# Minishell - 42 School Project - 1337 KH

![42 Project Badge](https://img.shields.io/badge/1337-Project-blue?style=for-the-badge&logo=42)
![GitHub code size](https://img.shields.io/github/languages/code-size/oussama-fa/minishell_42?style=flat-square)
![GitHub last commit](https://img.shields.io/github/last-commit/oussama-fa/minishell_42?style=flat-square)

A custom Unix shell written in C, replicating core features of Bash.  
Built from scratch to manage processes, parse and execute commands, handle redirections, pipes, environment variables, and more.

---

## 🧠 Overview

**Minishell** is one of the most complex projects in the 42 curriculum.  
It requires an in-depth understanding of Unix internals: from lexing and parsing shell input, to managing low-level system calls like `fork`, `execve`, `pipe`, and `dup2`.

This project was developed in collaboration with [sbaghdad](https://github.com/lboghdadyy), where:
- **Oussama FARAH/oufarah** focused on **execution, Built-in commands, pipes, environment, exit status**, and memory management.
- **Soufiane Baghdadi/sbaghdad** handled **expand, parsing, redirections, signal handling, syntax validation**, and argument expansion logic.

---

## 🍀 Project Structure
``` bash
minishell/
├── builtins/ # echo with option -n, cd, pwd, export, unset, env, exit
├── exec/ # execution, piping, forking
├── lexer/ # tokenizing input
├── parser/ # syntax tree and command structure
├── env/ # environment variable management
├── signals/ # signal handling
├── garbage/ # custom garbage collector
├── minishell.c # main shell loop
└── libft/ # custom C standard library same functions in libft
```
---

## 📷 Screenshots

<div align="center">
  <img src="minishell.png" alt="Minishell" width="700"/>
</div>

---

## ✨ Features

- ✅ Custom interactive shell prompt
- ✅ Environment variable expansion (`$HOME`, `$USER`, etc.)
- ✅ Built-in commands:
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- ✅ Input/output redirection:
  - `<`, `>`, `>>`
- ✅ Pipe support: `ls | grep txt | wc -l`
- ✅ Quote handling: `'`, `"`
- ✅ Exit status tracking with `$?`
- ✅ Heredoc (`<<`) support
- ✅ Signal handling: `Ctrl+C`, `Ctrl+\`
- ✅ Custom garbage collector for memory management
- ✅ Norminette-compliant (42 style guide)

---

## ⚙️ How It Works

Minishell executes a cycle of:
1. Reading input from the user.
2. Tokenizing and parsing the input into a command structure.
3. Executing the parsed commands, managing forks and redirections.
4. Cleaning up and returning to prompt.

---

## 📦 Installation

```bash
# Clone the repository
git clone https://github.com/oussama-fa/minishell_42.git
cd minishell_42

# Compile
make
```
## 🧪 Usage
Run the shell:
```bash
./minishell
```
Try a few commands:
```bash
minishell➤ echo -n Hello World
minishell➤ export NAME=oussama
minishell➤ echo $NAME
minishell➤ ls -l | grep .c | wc -l
minishell➤ cat << EOF
minishell➤ export a="ls   -la"
minishell➤ $a
total 100
drwxr-xr-x 5 oufarah 2024_khouribga   148 Jun 26 16:47 .
drwxr-xr-x 7 oufarah 2024_khouribga    96 Jun 26 16:27 ..
drwxr-xr-x 2 oufarah 2024_khouribga  4096 Jun 26 16:47 exec
-rw-r--r-- 1 oufarah 2024_khouribga  1928 Jun 26 16:27 garbage.c
drwxr-xr-x 7 oufarah 2024_khouribga   119 Jun 26 16:47 .git
-rw-r--r-- 1 oufarah 2024_khouribga  2420 Jun 26 16:27 Makefile
-rwxr-xr-x 1 oufarah 2024_khouribga 62144 Jun 26 16:47 minishell
-rw-r--r-- 1 oufarah 2024_khouribga  2295 Jun 26 16:27 minishell.c
-rw-r--r-- 1 oufarah 2024_khouribga  8517 Jun 26 16:27 minishell.h
drwxr-xr-x 3 oufarah 2024_khouribga  4096 Jun 26 16:47 parse
-rw-r--r-- 1 oufarah 2024_khouribga  2920 Jun 26 16:47 README.md

```

---
## 🧠 Technical Details

- *Language:* C

- *Parsing:* Handles quotes, redirections, expansions, pipes

- *Core Syscalls:* fork, execve, pipe, dup2, wait, access

- *Built-in Management:* Handled in separate logic without forking

- *Environment:* Custom linked list replacing envp

- *Memory:* Leak-free using custom garbage collector and handle file descrepter leaks

- *Signal Handling:* Custom behavior for SIGINT, SIGQUIT

---

## 🧩 Challenges
- Writing a parser that correctly interprets complex shell syntax

- Forking and managing multiple processes with file descriptor safety

- Managing memory leaks in dynamic command structures

---
## 📜 Norm & Requirements
✅ 42 Norminette Compliant

❌ No system() or other forbidden functions

✅ Fully leak-free (tested with valgrind)

✅ Behavior replicates Bash as much as possible

---

## 🤝 Team Members

*👨‍💻 Oussama FARAH*

- ✉️ **Email**: [oussama05farah@gmail.com](mailto:oussama05farah@gmail.com)
- 📱 **Instagram**: [@oussama._.farah](https://www.instagram.com/oussama._.farah/)

*👨‍💻 Soufiane Baghdadi*

- **Github**: [sbaghdad](https://github.com/lboghdadyy)

<div align="center"> <h2>Welcome to your own shell! 🐚</h2> <h3>Type away and enjoy hacking the Unix world! 🚀</h3> </div> 
