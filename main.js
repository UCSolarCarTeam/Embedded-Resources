// List of markdown files to load and render
const markdownFiles = [
  { file: './markdown-files/SPI.md', title: 'SPI' },
  // ADD NEW MARKDOWN FILES HERE
];

const REPO_IMAGE_BASE = 'https://ucsolarcarteam.github.io/Embedded-Resources/images';

const fixImagePaths = (mdText) => {
  // Replace ../images/... with link to images in the repo
  return mdText.replace(/\.\.\/images\//g, `${REPO_IMAGE_BASE}/`);
};

// Load the Markdown parser (e.g., marked.js)
const loadMarkdownParser = () => {
  return new Promise((resolve, reject) => {
    const script = document.createElement('script');
    script.src = 'https://cdn.jsdelivr.net/npm/marked/marked.min.js';
    script.onload = resolve;
    script.onerror = reject;
    document.head.appendChild(script);
  });
};

const renderMarkdownFiles = async () => {
  await loadMarkdownParser();

  const container = document.getElementById('markdown-container');

  for (const { file, title } of markdownFiles) {
    try {
      const res = await fetch(file);
      if (!res.ok) throw new Error(`Failed to load ${file}`);
      
      let mdText = await res.text();
      mdText = fixImagePaths(mdText);

      const html = marked.parse(mdText);

      // Create a details element for each markdown file
      const details = document.createElement('details');
      const summary = document.createElement('summary');
      summary.textContent = title;
      details.appendChild(summary);

      const contentDiv = document.createElement('div');
      contentDiv.innerHTML = html;
      details.appendChild(contentDiv);

      container.appendChild(details);
    } catch (err) {
      console.error(err);
    }
  }
};

renderMarkdownFiles();
