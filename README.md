# My Course Archive

A personal, static archive of materials from courses I've already completed — slides, notes, previous questions, assignments, project files, and more. Built with plain HTML, CSS and vanilla JavaScript. No backend, no database, no build step.

---

## How it's organized

```
course-archive/
│
├── index.html          Home page: stats, search, featured courses
├── courses.html         Full course listing with search + semester filter
├── course.html           Single-course template (reads ?code=XXXX from the URL)
│
├── css/
│   ├── style.css         All component styles + design tokens
│   └── responsive.css    Small-screen breakpoints
│
├── js/
│   ├── courses.js        ★ ALL course + file data lives here
│   ├── app.js             Home page + course listing logic (search, filters)
│   └── course-detail.js   Renders a single course page from courses.js
│
├── content/               Your actual files, organized by semester → course → category
│   ├── 1st-semester/
│   │   ├── CSE103-structured-programming/
│   │   │   ├── slides/
│   │   │   ├── notes/
│   │   │   ├── previous-questions/
│   │   │   ├── assignments/
│   │   │   ├── books/
│   │   │   ├── project/
│   │   │   └── resources/
│   │   └── ...
│   ├── 2nd-semester/
│   └── ...
│
└── README.md
```

### Why one course page (`course.html`), not one file per course?

With 20+ courses, generating a static HTML file per course would mean editing HTML every time you add a course. Instead, `course.html` is a single template that reads the course code from the URL (`course.html?code=CSE103`) and fills itself in from `js/courses.js`. That means **adding a course never requires writing any HTML** — only a JavaScript object.

### Why `content/` is organized by semester, then course, then category

This mirrors how course material naturally accumulates (you finish a semester, then a course within it), matches how the source material was already organized, and keeps the file tree scannable. Course folder names include the course code so they sort and search predictably, e.g. `CSE103-structured-programming`.

### Why data lives in `js/courses.js` instead of separate JSON files

For a project this size, a single `COURSES` array is easier to hand-edit than 20+ separate JSON files, and needs no fetch/build step — the browser just reads it directly, which keeps everything working from `file://` during local testing and from any static host once deployed. If your archive grows much larger later, you could split it into one JSON file per semester and fetch them — the rest of the site wouldn't need to change.

---

## A note on your Drive source

The site's course list, codes, names, semesters, and (where confirmed) faculty were pulled directly from your **"Study"** Drive folder — these are your real 20 courses across 1st–6th Semester, not placeholder data. Two things to know:

- **Faculty marked "TBD"** — I could only confirm the instructor for CSE103 and CSE251 from course outline PDFs already in the folder. Fill in the rest by editing the `faculty` field in `js/courses.js`.
- **Folders I deliberately did *not* mirror**, because they were duplicates or auto-generated clutter rather than real categories:
  - `CSE251 Mid slides-20260710T163332Z-2-001` (a Google-Drive auto-extract folder, sitting at the semester level by mistake — a duplicate of slides already inside `CSE251/Slides`)
  - `CSE 251 (MHR) (ALL)` and `CSE 251 (MHR) (ALL).zip` inside CSE251 (a full duplicate dump + its own zip archive of the same files)
  - A stray `final` folder inside CSE251 with no clear contents

  None of these were turned into `content/` folders. When you copy your real files over, only copy the *actual* category folders (Slides, Notes, Previous Questions, Reports, Books, etc.) — skip anything that looks like a timestamped export or an "(ALL)"-style dump of files you already have elsewhere.
- Two loose PDFs sat at the very top of "Study" (`Graduate Programs Cyber Security.pdf`, `BlueBook111.pdf`) — these are university-wide reference documents, not course material, so they weren't mapped to any course. If you want to keep them, a simple `content/general/` folder works well.

---

## How to add a new course

1. **Create the folder structure** under `content/<semester>/`:
   ```
   content/5th-semester/CSE246-algorithms/
     slides/
     notes/
     previous-questions/
     assignments/
     books/
     project/
     resources/
   ```
   (Only create the sub-folders you'll actually use — empty ones are harmless too.)

2. **Put your files inside the matching category folder.**

3. **Add the course to `js/courses.js`** — copy an existing course object and edit it:
   ```javascript
   {
     code: "CSE246",
     name: "Algorithms",
     faculty: "Dr. Jane Doe",
     semester: "5th Semester",
     term: "Spring 2025",       // optional — leave "" if unknown
     description: "Asymptotic analysis, divide-and-conquer, greedy and dynamic programming.",
     categories: {
       slides: [],
       notes: [],
       previousQuestions: [],
       assignments: [],
       books: [],
       project: [],
       resources: [],
     },
   },
   ```

4. **Save, refresh the site.** The course now appears on the home page, the "All Courses" page, and has its own page at `course.html?code=CSE246` — automatically.

---

## How to add a resource/file to an existing course

Say you have `content/5th-semester/CSE207-data-structures/previous-questions/final-2025.pdf` on disk. Find that course's object in `js/courses.js` and add an entry to the right category array:

```javascript
previousQuestions: [
  { title: "Final Exam 2025", file: "content/5th-semester/CSE207-data-structures/previous-questions/final-2025.pdf" },
],
```

`title` is what's shown on the course page. `file` is the relative path to the actual file. Refresh the page — it appears immediately, with a file-type badge (PDF/PPT/DOC/XLS/IMG/ZIP) generated automatically from the file extension.

---

## How missing/empty categories are handled

Every course lists all seven categories in `js/courses.js`, but a category is only **rendered** if its array has at least one item:

```javascript
notes: [],              // → "Notes" section is hidden entirely
previousQuestions: [ {...} ],  // → "Previous Questions" section shows, with 1 file
```

No configuration needed — `course-detail.js` filters out empty arrays before drawing the page. If **every** category for a course is empty, the page shows a friendly "No resources added yet" message instead of a blank page.

You can also add a category key that isn't in the default seven (e.g. `labManuals`) — just add it to the course's `categories` object and, optionally, give it a proper label/colour in `CATEGORY_CONFIG` at the top of `js/courses.js`. Unlisted category keys still render, using a neutral badge, so nothing breaks if you forget this step.

---

## Deploying via GitHub + Netlify

1. **Push to GitHub:**
   ```bash
   git init
   git add .
   git commit -m "Initial course archive"
   git branch -M main
   git remote add origin https://github.com/<your-username>/course-archive.git
   git push -u origin main
   ```

2. **Connect to Netlify:**
   - New site from Git → pick the repo.
   - Build command: *(leave blank — there is no build step)*
   - Publish directory: `.` (the repository root)
   - Deploy.

3. Every file reference in `js/courses.js` uses a **relative path** starting with `content/...`, so it works identically on `file://` while testing locally, and on your Netlify URL once deployed. Don't switch these to absolute paths like `C:\Users\...` or `/home/...`.

4. **Large files:** GitHub works fine for typical PDFs/slides, but has a 100MB per-file hard limit (and prefers repos well under 1GB). If any single file is unusually large, consider compressing it or hosting it externally (e.g. Google Drive) and linking to it instead of committing it — you can point a `file` entry straight at an external URL if needed.

---

## Local preview

No server required — you can open `index.html` directly in a browser. If your browser blocks local file access for the search/filtering scripts, run a tiny local server instead:

```bash
# Python 3
python -m http.server 8000
# then visit http://localhost:8000
```

---

## Design notes

- Plain solid accent colours only — no gradients, no glassmorphism. Each semester gets one consistent accent colour (used as a card border/tab underline) purely as a wayfinding aid.
- Two typefaces: **Fraunces** (serif, for course names/headings) and **IBM Plex Sans** (UI and body text), loaded from Google Fonts.
- All interactive states (hover, focus, mobile nav) are handled in plain CSS/JS — no dependencies.
"# My-Course-Archive" 
