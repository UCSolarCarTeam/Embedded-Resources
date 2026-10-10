# Embedded C Basics

Four short lessons, each with three exercises.

| Topic | Folder | Lesson | Exercises |
|---|---|---|---|
| 1. Variables and data types | `Lesson1/` | `lesson1.md` | `ex1a`, `ex1b`, `ex1c` |
| 2. Pointers, arrays, and strings | `Lesson2/` | `lesson2.md` | `ex2a`, `ex2b`, `ex2c` |
| 3. Bitwise operators and registers | `Lesson3/` | `lesson3.md` | `ex3a`, `ex3b`, `ex3c` |
| 4. Structs, enums, and state machines | `Lesson4/` | `lesson4.md` | `ex4a`, `ex4b`, `ex4c` |

## Folder layout

```
Basic/
  Makefile
  README.md
  test.h              shared test helper (don't edit)
  Lesson1/            lesson1.md, ex1a, ex1b, ex1c
  Lesson2/            lesson2.md, ex2a, ex2b, ex2c
  Lesson3/            lesson3.md, ex3a, ex3b, ex3c
  Lesson4/            lesson4.md, ex4a, ex4b, ex4c
  solutions/          finished versions of every exercise
```

## How it works

1. Read the lesson (`lessonN.md`).
2. Open an exercise file. It has function stubs marked `TODO`.
3. Fill in the functions, then build and run the exercise. The tests at the bottom of the file tell you what passes and what fails. **Don't edit the tests.**

## Build and run

You need `gcc` and `make`. From the `Basic/` folder, use the short exercise name:

```
make ex1a        # build and run exercise 1a
make ex2b        # build and run exercise 2b
make ex4c        # ... and so on, from ex1a to ex4c
```

Other commands:

| Command | What it does |
|---|---|
| `make` | Show the list of commands |
| `make exNN` | Build and run an exercise (e.g. `make ex1a`) |
| `make sol-exNN` | Build and run the **solution** for that exercise (e.g. `make sol-ex1a`) |
| `make check` | Compile every file without running it, to catch typos |
| `make clean` | Delete the `build/` folder |

Compiled programs go into `build/`, so your source folders stay clean.

The Makefile uses a Unix-style shell (Linux, macOS, WSL, or Git Bash / MSYS2 on Windows).

### Without make

If you prefer to compile by hand, run this from the `Basic/` folder. The `-I.` lets the compiler find `test.h`:

```
gcc -Wall -I. Lesson1/ex1a_fixed_width.c -o ex1a
./ex1a
```

## Reading the results

Each exercise prints which checks failed, with the line number, the expression, and the expected and actual values:

```
  FAIL (line 74): even[1]
        expected 3, got 2

2/16 checks passed
```

Failing checks at the start are normal. Keep editing and re-running until you see `All checks passed`.

## Tips

- Try each exercise yourself before looking at `solutions/`. Compare approaches afterwards.
- Print values while debugging. For bit work, print in hex: `printf("%X\n", v);`
- Keep compiler warnings on. When gcc warns, it is usually right.
- Put the folder under Git and commit after each finished exercise.
