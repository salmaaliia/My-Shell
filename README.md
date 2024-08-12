# MyShell

**MyShell** is a custom Unix-like shell implemented in C that provides a set of built-in commands and supports the execution of external commands. It includes several built-in commands for common file operations and environment manipulations, as well as the ability to handle standard bash commands. The shell supports

## Features

- **Built-in Commands**: Includes custom commands such as `mycp`, `mymv`, `mypwd`, `myecho`, `myhelp`, `myexit`, `mytype`, `envir`, `myfree`, `myuptime`.
- **Support for External Commands**: Can execute standard bash commands and other external programs.
- **Supports piping: allowing users to connect the output of one command directly to the input of another command.
- **Supports redirection: enabling users to redirect the output and error of commands to files or other locations, and to use files as input for commands.
- **Command-Line Interface**: Interactive shell environment where you can execute commands, view help messages, and manage files.

## Built-in Commands

Here’s a brief overview of each built-in command:

- **`mycp <source> <destination>`**: Copies a file from `<source>` to `<destination>`.
- **`mymv <source> <destination>`**: Moves a file from `<source>` to `<destination>`.
- **`mypwd`**: Prints the current working directory.
- **`myecho <message>`**: Prints `<message>` to the standard output.
- **`myhelp [command]`**: Displays help information for built-in commands. If no command is specified, lists all available commands.
- **`myexit`**: Exits the shell.
- **`mytype <command>`**: Displays the type of the specified command (built-in or external).
- **`envir [variable]`**: Prints all environment variables if no argument is provided. If a variable name is specified, prints the value of that variable.

## Usage

### Adding MyShell to Your PATH

To execute `MyShell` from any location, add its directory to your `PATH` environment variable:

1. **Compile MyShell** (see the next section for instructions).
2. **Move the compiled executable** to a directory included in your `PATH`, or add its directory to `PATH`.

   Example to add the directory to `PATH`:

   ```sh
   echo 'export PATH="$PATH:/home/user/Desktop/my_shell"' >> ~/.bashrc
   source ~/.bashrc
   
### Compiling MyShell

To compile `MyShell` with its various source files, use the following `gcc` command: 

  ```
gcc -o my_shell program.c mycp.c mymv.c mypwd.c myecho.c myhelp.c mycd.c envir.c external.c mytype.c piping.c myfree.c myuptime.c redirection.c terminate.c -lreadline -lhistory 
```
## Examples 

### Copying a File
```
mycp file1.txt file2.txt
```

### Moving a File
```
mymv file1.txt /new/location/file1.txt
```

### Printing the Current Directory
```
mypwd
```

### Echoing a Message
```
 myecho "Hello, world!"
```

### Getting Help
```
 myhelp

 myhelp mycp
```

### Exiting the Shell
```
myexit
```

### Checking Command Type
```
mytype mycp
```

### Viewing Environment Variables
```
envir
envir PATH
```
### pipe and redirection 
```
ls | grep p > output.txt
```

