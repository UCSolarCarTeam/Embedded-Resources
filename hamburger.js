const menuToggle = document.getElementById("menu-toggle");
const sidebar = document.getElementById("sidebar");
const markdownList = document.getElementById("markdown-list");

// Create a close button at the top of the sidebar
const closeButton = document.createElement("button");
closeButton.textContent = "×";
closeButton.classList.add("close-btn");
closeButton.addEventListener("click", () => {
  sidebar.classList.remove("open");
});
sidebar.prepend(closeButton);

export function populateMarkdownList(files, onFileSelect) {
  markdownList.innerHTML = "";
  files.forEach(entry => {
    const li = document.createElement("li");
    li.textContent = entry.title;
    li.addEventListener("click", () => {
      onFileSelect(entry);
      sidebar.classList.remove("open");
    });
    markdownList.appendChild(li);
  });
}

// Toggle sidebar visibility
menuToggle.addEventListener("click", () => {
  sidebar.classList.toggle("open");
});
