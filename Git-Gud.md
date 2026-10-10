# How to Git Gud

Git keeps a history of your work. Every time you finish something, you save a snapshot called a **commit**, and you can always go back. It also lets you share your work with others through a **remote** repository (for example on GitHub or GitLab).

In this lesson you will get a copy of the course repo, make your own branch, and save your first commit. You will use the same steps for every exercise after this.

---

## 1. One-time setup

Check that Git is installed:

```
git --version
```

Tell Git who you are. This is attached to every commit you make:

```
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```

(On Windows, run the commands in **Git Bash**.)

## 2. Set up an SSH key

An SSH key lets you talk to the remote without typing a password every time. You only do this once per computer.

**1. Check whether you already have a key:**

```
ls ~/.ssh/id_ed25519.pub
```

If it prints the file name, skip to step 3.

**2. Create a key.** Press Enter to accept the defaults:

```
ssh-keygen -t ed25519 -C "you@example.com"
```

**3. Show your public key and copy it:**

```
cat ~/.ssh/id_ed25519.pub
```

**4. Add it to your account.** On GitHub: *Settings → SSH and GPG keys → New SSH key*, then paste. On GitLab: *Preferences → SSH Keys*.

**5. Test the connection** (use `git@gitlab.com` for GitLab):

```
ssh -T git@github.com
```

You should see a greeting that includes your username.

> Never share the file without `.pub` (`id_ed25519`). That is your **private** key. Only the `.pub` file is safe to share.

## 3. Clone the repo (using SSH)

**Cloning** downloads a full copy of the repository to your computer. Use the **SSH** address, which looks like `git@github.com:owner/repo.git` (not the `https://` one). On the repo page, click the green **Code** button and choose the **SSH** tab.

```
git clone git@github.com:UCSolarCarTeam/Embedded-Resources.git
cd <repo>
```

Look around:

```
ls
git status
```

`git status` is the command you will use most. It tells you what branch you are on and what has changed.

## 4. Create your own branch

A **branch** is your own line of work, separate from everyone else's. The main branch (usually `main`) stays untouched while you work on yours.

Create a branch named after you, and switch to it. Use your first name in lowercase, followed by -training, with no spaces.

### New Method (Recommended)

```
git switch -c firstname-training
```

For example: `git switch -c nathan-training`. Use lowercase letters and hyphens, with no spaces.

### Old Method 

You can accomplish the same thing using the older git checkout command:

```
git checkout -b firstname-training
git checkout firstname-training
```

Both methods create a new branch and switch to it.

Check which branch you are currently on:

```
git branch
```

The branch with the `*` next to it is the one you are on. Everything you do from now on happens on your branch.

## 5. The basic loop: edit, add, commit

Git works in three steps:

```
edit files  →  git add  →  git commit
```

- **`git add`** chooses which changes go into the next snapshot (this is called *staging*).
- **`git commit`** saves the staged changes as a snapshot, with a message.

Try it now. Create a small file with your name in it:

```
echo "Hello, I am recruit YOUR_NAME, reporting for training!" > YOUR_NAME.txt
git status
```

Git shows the new file as **untracked**. Stage it, then commit:

```
git add YOUR_NAME.txt
git status
git commit -m "Add my hello file"
```

Check the history:

```
git log
```

You should see your commit at the top.

**Writing good commit messages:** keep them short and say what you did, for example `Finish ex1a` or `Fix off-by-one in ex2b`. Avoid messages like `stuff`.

## 6. See what you changed

Edit your file (add another line), then run:

```
git status         # which files changed
git diff           # exactly what changed (lines added and removed)
```

Stage and commit it again:

```
git add YOUR_NAME.txt
git commit -m "Add a second line"
```

To stage everything that changed at once, use `git add .`. Check `git status` first so you know what you are adding.

## 7. Push your branch to the remote

So far your commits only exist on your computer. **Pushing** uploads them. The first time you push a new branch, use `-u` so Git remembers where it goes:

```
git push -u origin firstname-training
```

After that, a plain `git push` is enough.

Open the repo page in your browser and look for your branch in the branch list.

## 8. What to do during this course

For every exercise:

1. Make sure you are on your own branch (`git branch`).
2. Solve the exercise and run it until all the checks pass.
3. Commit:
   ```
   git add .
   git commit -m "Finish ex1a"
   ```
4. Push when you finish a session: `git push`

Making a commit after each exercise gives you a clear history and a safe point to go back to.

**Don't commit build output.** The Makefile puts programs in a `build/` folder. To keep it out of Git, a file named `.gitignore` tells Git which files and folders to intentionally ignore. You can look inside and see the line written below:

```
build/
```

## 9. Undoing mistakes

| Situation | Command |
|---|---|
| Throw away edits to a file (not yet staged) | `git restore filename` |
| Unstage a file you added by mistake | `git restore --staged filename` |
| Fix the message of your last commit | `git commit --amend -m "New message"` |

Careful: `git restore filename` permanently discards your changes to that file.

## Cheat sheet

| Command | What it does |
|---|---|
| `git clone <ssh-url>` | Download a copy of the repo |
| `git status` | Show the current branch and what changed |
| `git switch -c <name>` | Create a new branch and switch to it |
| `git switch <name>` | Switch to an existing branch |
| `git branch` | List branches (`*` marks the current one) |
| `git add <file>` | Stage a file for the next commit |
| `git commit -m "message"` | Save a snapshot of the staged changes |
| `git diff` | Show changes that are not staged yet |
| `git log --oneline` | Show the commit history |
| `git push` | Upload your commits |
| `git pull` | Download new commits from the remote |

## Additional Resources

[Official Git Documentation](https://git-scm.com/docs)

[Getting Git Right](https://www.atlassian.com/git)

[Difference between Git and Github](https://stackoverflow.com/questions/13321556/difference-between-git-and-github)