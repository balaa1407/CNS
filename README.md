# PDF-to-Source Extractor

This repository contains a small utility to extract text from PDFs containing source code
and save them as language-detected source files.

Files added
- `scripts/pdf_to_java.py` - Extracts text from PDFs and writes language-appropriate files.
- `requirements.txt` - `pypdf` is required for PDF parsing.

Quick usage

Install dependencies:

```bash
python3 -m pip install -r requirements.txt
```

Write extracted files into `extracted_code/` (default):

```bash
python3 scripts/pdf_to_java.py . extracted_code
```

Write extracted files next to their original PDFs (inplace mode):

```bash
python3 scripts/pdf_to_java.py . inplace
```

Behavior
- The script heuristically detects a language and chooses an extension (.c, .java, .py, .cpp, .js, .php, .sql or .txt).
- If no extractable text is found, a small stub comment is written.

Notes
- The detection is heuristic and may not be perfect. If you want a different extension or formatting for a file, edit it manually.
- If you prefer all extracted files in a single directory, use the `extracted_code` output path.

If you want improvements (better language detection, per-PDF metadata, or automatic formatting), open an issue or request and I'll add them.
This folder contains the CNS lab programs and various cryptography-related programs. Includes the encryption and decryption code in C and Java.
