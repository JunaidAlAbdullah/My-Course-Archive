/* ==========================================================================
   course-detail.js
   Renders course.html based on the ?code=XXXX query parameter.
   Only categories that contain at least one file are rendered —
   that is the entire "hide missing categories" mechanism.
   ========================================================================== */

(function () {
  "use strict";

  const params = new URLSearchParams(window.location.search);
  const code = (params.get("code") || "").toUpperCase();
  const course = COURSES.find((c) => c.code.toUpperCase() === code);

  const root = document.getElementById("course-root");
  const crumbCourse = document.getElementById("crumb-course");

  if (!course) {
    root.innerHTML = `
      <div class="course-empty">
        <h1>Course not found</h1>
        <p>We couldn't find a course with the code <strong>${code || "(none given)"}</strong>.</p>
        <p><a href="courses.html">&larr; Back to all courses</a></p>
      </div>
    `;
    document.title = "Course not found · Course Archive";
    return;
  }

  document.title = `${course.code} · ${course.name} · Course Archive`;
  if (crumbCourse) crumbCourse.textContent = course.code;

  const accent = SEMESTER_COLORS[course.semester] || "blue";
  document.documentElement.style.setProperty("--accent-runtime", `var(--${accent})`);

  const totalCount = countResources(course);

  /* ---- header ---- */
  const header = document.createElement("div");
  header.className = "course-header";
  header.style.setProperty("--accent", `var(--${accent})`);
  header.innerHTML = `
    <div class="container">
      <span class="course-header__code">${course.code}</span>
      <h1>${course.name}</h1>
      ${course.description ? `<p class="lede">${course.description}</p>` : ""}
      <div class="course-meta">
        <div class="course-meta__item">
          <div class="course-meta__label">Faculty</div>
          <div class="course-meta__value">${course.faculty}</div>
        </div>
        <div class="course-meta__item">
          <div class="course-meta__label">Semester</div>
          <div class="course-meta__value">${course.semester}</div>
        </div>
        ${course.term ? `
        <div class="course-meta__item">
          <div class="course-meta__label">Term</div>
          <div class="course-meta__value">${course.term}</div>
        </div>` : ""}
        <div class="course-meta__item">
          <div class="course-meta__label">Resources</div>
          <div class="course-meta__value">${totalCount}</div>
        </div>
      </div>
      ${course.outline ? `
      <a class="outline-link" href="${course.outline}" target="_blank" rel="noopener">
        View course outline
      </a>` : ""}
    </div>
  `;

  /* ---- resource categories ---- */
  const body = document.createElement("div");
  body.className = "container section";

  const activeCategories = Object.entries(course.categories).filter(([, list]) => list.length > 0);

  if (activeCategories.length === 0) {
    body.innerHTML = `
      <div class="empty-state">
        <h3>No resources added yet</h3>
        <p>Once you copy files into this course's folders and list them in <code>js/courses.js</code>, they'll appear here automatically.</p>
      </div>
    `;
  } else {
    activeCategories.forEach(([key, list]) => {
      const config = CATEGORY_CONFIG[key] || { label: key, color: "purple" };
      const section = document.createElement("section");
      section.className = "category";
      section.innerHTML = `
        <div class="category__head">
          <span class="category__badge" style="--badge-tint: var(--${config.color}-tint); --badge-color: var(--${config.color});">
            ${config.label}
          </span>
          <span class="category__count">${list.length} file${list.length === 1 ? "" : "s"}</span>
        </div>
        <ul class="resource-list"></ul>
      `;
      const ul = section.querySelector(".resource-list");
      list.forEach((item) => {
        const ext = getFileExt(item.file);
        const li = document.createElement("li");
        li.className = "resource-item";
        li.innerHTML = `
          <a href="${item.file}" target="_blank" rel="noopener">
            <span class="file-chip ${fileChipClass(ext)}">${fileTypeLabel(ext).slice(0, 4)}</span>
            <span class="resource-item__text">
              <span class="resource-item__title">${item.title}</span>
              <span class="resource-item__type">${fileTypeLabel(ext)}</span>
            </span>
          </a>
        `;
        ul.appendChild(li);
      });
      body.appendChild(section);
    });
  }

  root.appendChild(header);
  root.appendChild(body);
})();
