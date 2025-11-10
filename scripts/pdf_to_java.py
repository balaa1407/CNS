#!/usr/bin/env python3
"""
Extract text from all PDFs in the repository and write each to a language-appropriate
source file in the `extracted_code/` directory. The script heuristically detects the
programming language from the extracted text and chooses an extension (e.g., .c, .java, .py).

Usage:
  python3 scripts/pdf_to_java.py [pdf_dir] [out_dir]

If no args are given, the script searches the current directory recursively.
"""
from pathlib import Path
import sys
import re

try:
    # pypdf is the modern maintained package (previously PyPDF2)
    from pypdf import PdfReader
except Exception:
    print("Missing required package 'pypdf'. Install with: pip install pypdf")
    raise


def extract_text_from_pdf(path: Path) -> str:
    reader = PdfReader(str(path))
    texts = []
    for page in reader.pages:
        try:
            texts.append(page.extract_text() or "")
        except Exception:
            texts.append("")
    return "\n".join(texts)


def detect_language_and_extension(text: str) -> str:
    """Return a file extension (including dot) inferred from text heuristics."""
    t = text.lower()

    # Java
    if ('import java' in t) or ('public class' in t) or ('public static void main' in t) or ('system.out.println' in t):
        return '.java'

    # C (look for includes and printf/scanf)
    if '#include' in t or 'printf(' in t or 'scanf(' in t or 'malloc(' in t:
        return '.c'

    # C++
    if 'using namespace std' in t or 'std::' in t or 'cout<<' in t:
        return '.cpp'

    # Python
    if re.search(r'^\s*def\s+\w+\s*\(', text, re.M) or 'if __name__' in t or '\nimport ' in t:
        return '.py'

    # JavaScript
    if 'console.log(' in t or re.search(r'function\s+\w+\s*\(', text):
        return '.js'

    # PHP
    if '<?php' in t:
        return '.php'

    # SQL (simple heuristic)
    if re.search(r'\bselect\b|\binsert\b|\bupdate\b|\bcreate table\b', t):
        return '.sql'

    # Default to text
    return '.txt'


def normalize_header_for_extension(ext: str, pdfname: str) -> str:
    """Return a short header comment appropriate to the extension."""
    if ext == '.java' or ext == '.c' or ext == '.cpp' or ext == '.js' or ext == '.php':
        return f"// Extracted from {pdfname}\n\n"
    if ext == '.py':
        return f"# Extracted from {pdfname}\n\n"
    if ext == '.sql':
        return f"-- Extracted from {pdfname}\n\n"
    return f"// Extracted from {pdfname}\n\n"


def main():
    pdf_dir = Path(sys.argv[1]) if len(sys.argv) > 1 else Path('.')
    out_dir = Path(sys.argv[2]) if len(sys.argv) > 2 else Path('extracted_code')
    out_dir.mkdir(parents=True, exist_ok=True)

    pdfs = list(pdf_dir.rglob('*.pdf'))
    if not pdfs:
        print(f"No PDF files found under {pdf_dir.resolve()}")
        return

    print(f"Found {len(pdfs)} PDF(s). Extracting to: {out_dir.resolve()}")

    for pdf in pdfs:
        try:
            text = extract_text_from_pdf(pdf)
            if not text.strip():
                # No extractable text
                ext = '.txt'
                header = f"// (No extractable text found in {pdf.name})\n"
                outname = pdf.stem + ext
                outfile = out_dir / outname
                with outfile.open('w', encoding='utf-8') as f:
                    f.write(header)
                print(f"Wrote (empty): {outfile}")
                continue

            ext = detect_language_and_extension(text)
            header = normalize_header_for_extension(ext, pdf.name)

            outname = pdf.stem + ext
            outfile = out_dir / outname
            with outfile.open('w', encoding='utf-8') as f:
                f.write(header)
                f.write(text)

            print(f"Wrote: {outfile} (detected {ext})")
        except Exception as exc:
            print(f"Failed to extract {pdf}: {exc}")


if __name__ == '__main__':
    main()
