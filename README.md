# pipex
Pipex is a project that introduces students to process communication using pipes in Unix systems. The goal is to mimic the behavior of the shell command:
```bash
< infile cmd1 | cmd2 > outfile

### Command Breakdown

- `< infile`  
  Redirects input for `cmd1` from a file named `infile`.

- `cmd1 | cmd2`  
  Passes the output of `cmd1` as input to `cmd2` using a pipe.

- `> outfile`  
  Redirects the final output of `cmd2` to a file named `outfile`.
