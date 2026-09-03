/* ==========================================================================
   courses.js
   ---------------------------------------------------------------------
   This is the ONLY file you should need to edit to add courses or files.
   The UI (app.js / course-detail.js) reads everything from here.

   - Add a new course:      push a new object into the COURSES array.
   - Add a file to a course: push a new object into that course's
                              categories.<categoryKey> array.
   - Add a brand-new category (e.g. "labManuals"): just use a new key
     inside `categories` — the UI will render it automatically using
     the fallback badge style, or add it to CATEGORY_CONFIG below to
     give it a proper label and colour.
   - A category with an empty array [] is simply not shown. That's how
     "missing categories" are handled — no code changes needed.
   ========================================================================== */

/* ---- Which accent colour represents each semester on cards/tabs ---- */
const SEMESTER_ORDER = [
  "1st Semester",
  "2nd Semester",
  "3rd Semester",
  "4th Semester",
  "5th Semester",
  "6th Semester",
];

const SEMESTER_COLORS = {
  "1st Semester": "blue",
  "2nd Semester": "purple",
  "3rd Semester": "orange",
  "4th Semester": "green",
  "5th Semester": "red",
  "6th Semester": "pink",
};

/* ---- Category display config: label + colour badge ----
   Key must match the key used inside a course's `categories` object.
   Anything not listed here still renders, using a neutral badge. */
const CATEGORY_CONFIG = {
  slides: { label: "Slides", color: "blue" },
  notes: { label: "Notes", color: "purple" },
  previousQuestions: { label: "Previous Questions", color: "orange" },
  assignments: { label: "Assignments", color: "green" },
  books: { label: "Books & References", color: "yellow" },
  project: { label: "Project Files", color: "green" },
  labReports: { label: "Lab Reports", color: "red" },
  labManuals: { label: "Lab Manuals", color: "red" },
  presentations: { label: "Presentation Slides", color: "pink" },
  resources: { label: "Resources & Links", color: "pink" },
  misc: { label: "Miscellaneous", color: "purple" },
};

/* ---- Course data ----
   Sourced from the user's own "Study" archive (East West University,
   CSE program). Faculty marked "TBD" were not yet confirmed and
   should be filled in by hand — see README "Adding a new course".

   Two courses (CSE103, CSE251) are populated with real resource
   entries as a working example. All other courses are set up with
   real course codes/names/semesters but empty resource lists, ready
   for you to fill in as you copy files over. Empty categories are
   simply omitted from the course page automatically. */
const COURSES = [

  // ---------------- 1st Semester ----------------
  {
    code: "MAT101",
    name: "Differential & Integral Calculus",
    faculty:"Kazi Nusrat Islam - KNI",
    semester: "1st Semester",
    term: "",
    description: "Limits, continuity, differentiation and integration of single-variable functions, with applications.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "CSE106",
    name: "Discrete Mathematics",
    faculty: "Dr. Muhammad Salah Uddin - DSU",
    semester: "1st Semester",
    term: "Fall 2024",
    outline: "content/1st-semester/CSE106-discrete-mathematics/resources/CSE106course-outline.pdf",
    description: "Logic, sets, relations, combinatorics and graph theory foundations for computer science.",
    categories: {
      slides: [
        { title: "Counting", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Counting.pdf" },
        { title: "Discrete Azad Sir", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Discrete Azir Sir.pdf" },
        { title: "Functions Part 2", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Functions Part 2.pdf" },
        { title: "Functions", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Functions.pdf" },
        { title: "Graph", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Graph.pdf" },
        { title: "Introduction to Proof", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Introduction to Proof.pdf" },
        { title: "Introduction to Trees", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Introduction to Trees.pdf" },
        { title: "Mathematical Induction", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Mathematical Induction.pdf" },
        { title: "Pigeonhole", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Pigeonhole.pdf" },
        { title: "Predicate Logic", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Predicate Logic.pdf" },
        { title: "Propositional Logic", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Propositional Logic.pdf" },
        { title: "Recusive Function", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Recusive Function.pdf" },
        { title: "Relations Slide", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Relations Slide.pdf" },
        { title: "Set", file: "content/1st-semester/CSE106-discrete-mathematics/slides/Set.pdf" },
      ],
      notes: [],
      previousQuestions: [
        { title: "Quiz", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/QUIZ(QS)-SPRING2023.jpg" },
        { title: "Mid", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/MID 01(QS)- SUMMER 2023.jpg" },
        { title: "Mid", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/MID 02 (QS) - SUMMER 2021,SEC4.jpg" },
        { title: "Mid", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/MID 02(QS) - FALL 2020, SEC-7.jpg" },
        { title: "Mid", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/MID 02(QS) - FALL 2020, SEC-8.jpg" },
        { title: "Mid", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/MID 02(QS) - FALL 2021,SEC5.jpg" },
        { title: "Mid", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/MID 02(QS) - SPRING 2023.jpg" },
        { title: "Mid", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/MID 02(QS)-DSU.jpg" },
        { title: "Mid", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/MID 02(QS)-SPRING 2023-SEC7.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/Final (2).jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/Final Summer21.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/FINAL(QS)-FALL2020-SEC7.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/FINAL(QS)-FALL2020-SEC8.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/FINAL(QS)-FALL2022-SEC7-PART1.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/FINAL(QS)-SPRING2021-SEC4.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/FINAL(QS)-SUMMER2021-SEC4.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/Final.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/Final QS-DSU -1.jpg" },
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/previous-questions/Final QS-DSU -1 (2).jpg" },

      ],
      assignments: [],
      books: [
        { title: "Discrete Mathematics 8th edition", file: "content/1st-semester/CSE106-discrete-mathematics/books/Discrete Mathematics 8th edition.pdf" }
      ],
      project: [
        { title: "Final", file: "content/1st-semester/CSE106-discrete-mathematics/project/CSE106 Project.zip" }
      ],
      resources: []
    },
  },
  {
    code: "ENG101",
    name: "Basic English",
    faculty: "ANISA MEHEDI - ANISA",
    semester: "1st Semester",
    term: "FALL 2024",
    outline: "content/1st-semester/ENG101-basic-english/resources/ENG101 Course Outline.pdf",
    description: "Foundational English grammar, comprehension and writing skills.",
    categories: {
      slides: [
        { title: "Course Compilation", file: "content/1st-semester/ENG101-basic-english/slides/ENG101 Course Compilation.pdf" },
      ],
      notes: [],
      previousQuestions: [


      ],
      assignments: [],
      books: [],

      project: [],
      resources: []
    },
  },
  {
    code: "CSE103",
    name: "Structured Programming",
    faculty: "Md. Ashraful Haider Chowdhury - MAHCY",
    semester: "1st Semester",
    term: "Fall 2024",
    description: "Introduction to structured programming in C: control flow, functions, arrays, pointers, structures and file handling.",
    outline: "content/1st-semester/CSE103-structured-programming/resources/course-outline.pdf",
    categories: {
      slides: [
        { title: "Lecture 1", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 1.pdf" },
        { title: "Lecture 2", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 2.pdf" },
        { title: "Lecture 3", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 3.pdf" },
        { title: "Lecture 4", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 4.pdf" },
        { title: "Lecture 5", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 5.pdf" },
        { title: "Lecture 6 Array", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 6 Array.pdf" },
        { title: "Lecture 6 Loop", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 6 Loop.pdf" },
        { title: "Lecture 7", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 7.pdf" },
        { title: "Lecture 8", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 8.pdf" },
        { title: "Lecture 9", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 9.pdf" },
        { title: "Lecture 10", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 10.pdf" },
        { title: "Lecture 11", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 11.pdf" },
        { title: "Lecture 12", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 12.pdf" },
        { title: "Lecture 13", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 13.pdf" },
        { title: "Lecture 14", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 14.pdf" },
        { title: "Lecture 15", file: "content/1st-semester/CSE103-structured-programming/slides/lecture 15.pdf" },
      ],
      notes: [],
      Practice_Problem: [
        { title: "C Practice Problems Pattern", file: "content/1st-semester/CSE103-structured-programming/previous-questions/C Practice Problems Pattern(Nested loop).pdf" },
        { title: "C practice problems(2D Array)", file: "content/1st-semester/CSE103-structured-programming/previous-questions/C practice problems(2D Array).pdf" },
        { title: "C practice problems(Loop)", file: "content/1st-semester/CSE103-structured-programming/previous-questions/C practice problems(Loop).pdf" },
        { title: "C practice problems(Pointer)", file: "content/1st-semester/CSE103-structured-programming/previous-questions/C practice problems(Pointer).pdf" },
        { title: "C practice problems(Recursion)", file: "content/1st-semester/CSE103-structured-programming/previous-questions/C practice problems(Recursion).pdf" },
        { title: "C practice problems(String)", file: "content/1st-semester/CSE103-structured-programming/previous-questions/C practice problems(String).pdf" },
        { title: "C practice problems(Structure)", file: "content/1st-semester/CSE103-structured-programming/previous-questions/C practice problems(Structure).pdf" },
        { title: "Call by Value vs Call by Reference", file: "content/1st-semester/CSE103-structured-programming/previous-questions/Call by Value vs Call by Reference.pdf" },
        { title: "loop practice problems", file: "content/1st-semester/CSE103-structured-programming/previous-questions/loop practice problems.pdf" },
        { title: "practice problem 1d array", file: "content/1st-semester/CSE103-structured-programming/previous-questions/practice problem 1d array.pdf" },
        { title: "practice problem 2", file: "content/1st-semester/CSE103-structured-programming/previous-questions/practice problem 2.pdf" },
        { title: "practice problem function", file: "content/1st-semester/CSE103-structured-programming/previous-questions/practice problem function.pdf" },
        { title: "practice problem", file: "content/1st-semester/CSE103-structured-programming/previous-questions/practice problem.pdf" },
      ],
      assignments: [],
      books: [
        { title: "Programming in ANSI", file: "content/1st-semester/CSE103-structured-programming/books/ansi-c-balaguruswamy-c-language-PDFDrive.com-.pdf" },
        { title: "Programming in ANSI C", file: "content/1st-semester/CSE103-structured-programming/books/Programming-in-ANSI-C.pdf" },
      ],
      project: [
        { title: "Library Management System", file: "content/1st-semester/CSE103-structured-programming/project/CSE103 Project.zip" },
      ],
      resources: [],
    },
  },

  // ---------------- 2nd Semester ----------------
  {
    code: "MAT102",
    name: "Differential Equations & Special Functions",
    faculty: "Md. Ashraf Hossain - ASHRAF",
    semester: "2nd Semester",
    term: "",
    description: "Ordinary differential equations, series solutions and special functions.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "ENG102",
    name: "Composition and Communication Skills",
    faculty: "ANISA MEHEDI - ANISA",
    semester: "2nd Semester",
    term: "Spring 2024",
    outline: "content/2nd-semester/ENG102-composition-and-communication-skills/resources/ENG102 Course Outline.pdf",
    description: "Academic writing, composition structure and oral communication practice.",
    categories:
    {
      slides: [
         {title: "Course Compilation", file: "content/2nd-semester/ENG102-composition-and-communication-skills/slides/ENG102 Course Compilation.pdf" }
      ],
      notes: [],
      previousQuestions: [
        { title: "Quiz 1", file: "content/2nd-semester/ENG102-composition-and-communication-skills/previous-questions/Quiz 1 Spring 2025.JPG" },
        { title: "Quiz 2", file: "content/2nd-semester/ENG102-composition-and-communication-skills/previous-questions/Quiz 2 Spring 2025.JPG" },
        { title: "Mid Page 1", file: "content/2nd-semester/ENG102-composition-and-communication-skills/previous-questions/Mid Spring 2025.jpg" },
        { title: "MId page 2", file: "content/2nd-semester/ENG102-composition-and-communication-skills/previous-questions/Mid Spring 2025 (2).jpg" },
      ],
      assignments: [
        { title: "Self-Development and Communication", file: "content/2nd-semester/ENG102-composition-and-communication-skills/assignments/Term Paper.pdf" },
      ],
      books: [],
      project: [],
      resources: []
    },
  },
  {
    code: "CHE109",
    name: "Engineering Chemistry-I",
    faculty: "Dr. Zubair Hasan - ZUH",
    semester: "2nd Semester",
    term: "",
    description: "Core chemistry concepts relevant to engineering practice.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },

  // ---------------- 3rd Semester ----------------
  {
    code: "CSE110",
    name: "Object Oriented Programming",
    faculty: "Dr. Muhammad Salah Uddin - DSU",
    semester: "3rd Semester",
    term: "",
    description: "OOP principles in C++/Java: classes, inheritance, polymorphism, encapsulation and exception handling.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "MAT104",
    name: "Co-ordinate Geometry & Vector Analysis",
    faculty: "Dr. Md. Shahidul Islam - DSHI",
    semester: "3rd Semester",
    term: "",
    description: "Coordinate geometry in 2D/3D and vector calculus fundamentals.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "PHY109",
    name: "Engineering Physics-I",
    faculty: "Md. Mahfuzul Haque - MMHQ",
    semester: "3rd Semester",
    term: "",
    description: "Mechanics, waves and thermodynamics for engineering students.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },

  // ---------------- 4th Semester ----------------
  {
    code: "MAT205",
    name: "Linear Algebra & Complex Variables",
    faculty: "Dr. Md. Shariful Alam - SHARIF",
    semester: "4th Semester",
    term: "",
    description: "Matrices, vector spaces, eigenvalues, and complex analysis basics.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "STA102",
    name: "Statistics and Probability",
    faculty: "DR. AFSANA AL SHARMIN - AAS",
    semester: "4th Semester",
    term: "",
    description: "Probability theory, distributions, estimation and hypothesis testing.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "CSE209",
    name: "Electrical Circuits",
    faculty: "Dr. Sayeed Mahmud Ullah - DSMU",
    semester: "4th Semester",
    term: "",
    description: "DC/AC circuit analysis, network theorems and transient response.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "CSE200",
    name: "Computer-Aided Engineering Drawing",
    faculty: "Antu Chowdury - ANTU",
    semester: "4th Semester",
    term: "",
    description: "CAD fundamentals and technical drawing conventions.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },

  // ---------------- 5th Semester ----------------
  {
    code: "CSE302",
    name: "Database Systems",
    faculty: "Antu Chowdhury - ANTU",
    semester: "5th Semester",
    term: "",
    description: "Relational model, SQL, normalization, transactions and database design.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "ECO7101",
    name: "Principles of Microeconomics",
    faculty: "DR. M. AMIR HUSSAIN - AMRH",
    semester: "5th Semester",
    term: "",
    description: "Supply and demand, market structures, and consumer/producer theory.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "CSE207",
    name: "Data Structures",
    faculty: "Ahmed Abdal Shafi Rasel - AASR",
    semester: "5th Semester",
    term: "",
    description: "Arrays, linked lists, stacks, queues, trees, graphs and their algorithms.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },

  // ---------------- 6th Semester ----------------
  {
    code: "GEN7226",
    name: "Emergence of Bangladesh",
    faculty: "Md. Abdullah Al Hasan Chowdhury - MAAHC",
    semester: "6th Semester",
    term: "",
    description: "History and socio-political emergence of Bangladesh.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "PHY209",
    name: "Engineering Physics-II",
    faculty: "Md. Mahfuzul Haque - MMHQ",
    semester: "6th Semester",
    term: "",
    description: "Electromagnetism, optics and modern physics for engineers.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "CSE325",
    name: "Operating Systems",
    faculty: "Shatabdi Roy Moon - MOON",
    semester: "6th Semester",
    term: "",
    description: "Processes, scheduling, memory management, concurrency and file systems.",
    categories: { slides: [], notes: [], previousQuestions: [], assignments: [], books: [], project: [], resources: [] },
  },
  {
    code: "CSE251",
    name: "Electronic Circuits",
    faculty: "Dr. Md. Habibur Rahman - MHR",
    semester: "6th Semester",
    term: "Summer 2026",
    description: "Diodes, BJTs, MOSFETs and operational amplifiers: theory, design and lab practice.",
    outline: "content/6th-semester/CSE251-electronic-circuits/resources/course-outline.pdf",
    categories: {
      slides: [
        { title: "Lecture Slides (MHR, full set)", file: "content/6th-semester/CSE251-electronic-circuits/slides/cse251-lecture-slides.pdf" },
        { title: "Midterm Slides", file: "content/6th-semester/CSE251-electronic-circuits/slides/cse251-midterm-slides.pdf" },
      ],
      notes: [
        { title: "Notes (by Mahathir)", file: "content/6th-semester/CSE251-electronic-circuits/notes/cse251-notes-mahathir.pdf" },
        { title: "Notes (by Toushik)", file: "content/6th-semester/CSE251-electronic-circuits/notes/cse251-notes-toushik.pdf" },
      ],
      previousQuestions: [
        { title: "Previous Semester Questions", file: "content/6th-semester/CSE251-electronic-circuits/previous-questions/cse251-previous-questions.pdf" },
      ],
      assignments: [],
      books: [],
      project: [],
      labReports: [
        { title: "Lab Reports", file: "content/6th-semester/CSE251-electronic-circuits/resources/lab-reports.pdf" },
      ],
      resources: [],
    },
  },
];

/* ---- helpers used by app.js / course-detail.js ---- */

function courseSlug(course) {
  return course.code.toLowerCase();
}

function countResources(course) {
  return Object.values(course.categories).reduce((sum, list) => sum + list.length, 0);
}

function getFileExt(path) {
  const clean = path.split("?")[0];
  const match = clean.match(/\.([a-zA-Z0-9]+)$/);
  return match ? match[1].toLowerCase() : "";
}

function fileChipClass(ext) {
  if (ext === "pdf") return "file-chip--pdf";
  if (["ppt", "pptx"].includes(ext)) return "file-chip--ppt";
  if (["doc", "docx"].includes(ext)) return "file-chip--doc";
  if (["xls", "xlsx", "csv"].includes(ext)) return "file-chip--xls";
  if (["png", "jpg", "jpeg", "gif", "webp"].includes(ext)) return "file-chip--img";
  if (["zip", "rar", "7z"].includes(ext)) return "file-chip--zip";
  return "file-chip--other";
}

function fileTypeLabel(ext) {
  if (!ext) return "FILE";
  return ext.toUpperCase();
}
