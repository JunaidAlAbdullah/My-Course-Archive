/* ==========================================================================
   app.js
   Shared behaviour for index.html and courses.html:
   - mobile nav toggle
   - stat counters
   - course card rendering
   - client-side search (code / name / faculty)
   - semester filter tabs (courses.html only)
   ========================================================================== */

(function () {
  "use strict";

  /* ---- mobile nav ---- */
  const navToggle = document.querySelector(".nav-toggle");
  const siteNav = document.querySelector(".site-nav");
  if (navToggle && siteNav) {
    navToggle.addEventListener("click", () => {
      const isOpen = siteNav.classList.toggle("is-open");
      navToggle.setAttribute("aria-expanded", String(isOpen));
    });
  }

  /* ---- build a single course card element ---- */
  function renderCourseCard(course) {
    const accent = SEMESTER_COLORS[course.semester] || "blue";
    const count = countResources(course);
    const a = document.createElement("a");
    a.href = `course.html?code=${encodeURIComponent(course.code)}`;
    a.className = "course-card";
    a.style.setProperty("--card-accent", `var(--${accent})`);

    a.innerHTML = `
      <div class="course-card__top">
        <span class="course-card__code">${course.code}</span>
        <span class="course-card__term">${course.term || course.semester}</span>
      </div>
      <div class="course-card__name">${course.name}</div>
      <div class="course-card__faculty">${course.faculty}</div>
      <div class="course-card__foot">
        <span>${course.semester}</span>
        <span><span class="resource-count">${count}</span> resource${count === 1 ? "" : "s"}</span>
      </div>
    `;
    return a;
  }

  function renderGrid(container, courses, emptyMessage) {
    container.innerHTML = "";
    if (courses.length === 0) {
      const empty = document.createElement("div");
      empty.className = "empty-state";
      empty.innerHTML = `<h3>No courses found</h3><p>${emptyMessage}</p>`;
      container.appendChild(empty);
      return;
    }
    courses.forEach((course) => container.appendChild(renderCourseCard(course)));
  }

  /* ---- search matching ---- */
  function matchesQuery(course, query) {
    if (!query) return true;
    const q = query.trim().toLowerCase();
    return (
      course.code.toLowerCase().includes(q) ||
      course.name.toLowerCase().includes(q) ||
      course.faculty.toLowerCase().includes(q)
    );
  }

  /* ==========================================================================
     Home page (index.html)
     ========================================================================== */
  const homeGrid = document.getElementById("home-course-grid");
  if (homeGrid) {
    const statTotal = document.getElementById("stat-total-courses");
    const statResources = document.getElementById("stat-total-resources");
    const statSemesters = document.getElementById("stat-total-semesters");
    const searchInput = document.getElementById("home-search");

    const totalResources = COURSES.reduce((sum, c) => sum + countResources(c), 0);
    if (statTotal) statTotal.textContent = COURSES.length;
    if (statResources) statResources.textContent = totalResources;
    if (statSemesters) statSemesters.textContent = new Set(COURSES.map((c) => c.semester)).size;

    // Show most-recently-added-feeling set: courses with the most resources first,
    // falling back to semester order. Cap to a handful so the homepage stays light.
    function homeCourseList(query) {
      return COURSES
        .filter((c) => matchesQuery(c, query))
        .sort((a, b) => countResources(b) - countResources(a));
    }

    function renderHome(query) {
      const list = query ? homeCourseList(query) : homeCourseList("").slice(0, 8);
      renderGrid(homeGrid, list, "Try a different course code, name, or faculty.");
    }

    renderHome("");

    if (searchInput) {
      searchInput.addEventListener("input", (e) => renderHome(e.target.value));
    }
  }

  /* ==========================================================================
     Full listing page (courses.html)
     ========================================================================== */
  const listGrid = document.getElementById("courses-grid");
  if (listGrid) {
    const searchInput = document.getElementById("courses-search");
    const tabsWrap = document.getElementById("semester-tabs");
    const countLabel = document.getElementById("courses-count");
    let activeSemester = "all";

    function buildTabs() {
      const semesters = ["all", ...SEMESTER_ORDER.filter((s) => COURSES.some((c) => c.semester === s))];
      tabsWrap.innerHTML = "";
      semesters.forEach((sem) => {
        const btn = document.createElement("button");
        btn.type = "button";
        btn.className = "semester-tab";
        btn.setAttribute("aria-pressed", String(sem === activeSemester));
        btn.textContent = sem === "all" ? "All Semesters" : sem;
        btn.addEventListener("click", () => {
          activeSemester = sem;
          buildTabs();
          renderList(searchInput ? searchInput.value : "");
        });
        tabsWrap.appendChild(btn);
      });
    }

    function renderList(query) {
      const list = COURSES.filter((c) => {
        const semOk = activeSemester === "all" || c.semester === activeSemester;
        return semOk && matchesQuery(c, query);
      });
      renderGrid(listGrid, list, "Try a different course code, name, faculty, or semester tab.");
      if (countLabel) countLabel.textContent = `${list.length} course${list.length === 1 ? "" : "s"}`;
    }

    buildTabs();
    renderList("");

    if (searchInput) {
      searchInput.addEventListener("input", (e) => renderList(e.target.value));
    }
  }
})();
