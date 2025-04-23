# Pipex: Unix Pipe Mechanism Implementation

## Project Overview

Pipex is an advanced project of implementing the Unix pipe mechanism in C. The program recreates the functionality of shell command pipelines, specifically emulating the behavior of commands like `< file1 cmd1 | cmd2 > file2`. This project provides deep insight into how processes communicate in Unix-based systems and demonstrates fundamental concepts of inter-process communication.

## Educational Objectives

This project aims to:
- Develop a thorough understanding of Unix process management
- Master inter-process communication using pipes
- Implement file redirection similar to shell operators (`<`, `>`)
- Handle command execution with proper argument parsing
- Manage memory and file descriptors efficiently
- Apply error handling in a multi-process environment

## Key Concepts and Skills Demonstrated

1. **Process Creation and Management**: Using `fork()` to create child processes
2. **Inter-Process Communication**: Implementing pipes with `pipe()` to connect processes
3. **File Descriptor Manipulation**: Redirecting standard input/output with `dup2()`
4. **Command Execution**: Using `execve()` to run shell commands
5. **Path Resolution**: Finding executable files in the system PATH
6. **Error Handling**: Robust error management with proper cleanup
7. **Memory Management**: Preventing memory leaks in complex process hierarchies

## Features and Functionality

### Mandatory Features
- Takes 4 arguments: `file1`, `cmd1`, `cmd2`, `file2`
- Reads input from `file1`
- Executes `cmd1` with input from `file1`
- Pipes the output of `cmd1` to the input of `cmd2`
- Redirects the output of `cmd2` to `file2`
- Handles command arguments and parameters
- Manages processes and their termination
+ I implemented straight redirection, as well.
  
### Bonus Features
- Supports multiple commands and pipes (e.g., `cmd1 | cmd2 | cmd3 | ... | cmdn`)
- Implements heredoc functionality (`<<` operator) with custom delimiter
- Supports append redirection (`>>` operator)

## Technical Approach

This project employs several key approaches:

1. **Process Forking**: It's better if each command runs in its own child process, isolated from others
2. **Pipe Architecture**: Data flows through pipes connecting the processes
3. **File Descriptor Redirection**: Standard input/output is redirected to connect processes
4. **Command Parsing**: Commands and their arguments are parsed and prepared for execution
5. **Path Resolution Algorithm**: The PATH environment variable is parsed to find executable files
6. **Resource Management**: Systematic closing of file descriptors and freeing of memory

These approaches allow for efficient inter-process communication while maintaining security through process isolation. The architecture mirrors the actual implementation in Unix-like operating systems.

## Technologies Used

- **C Programming Language**: Core implementation
- **Unix System Calls**:
  - `fork()`: For process creation
  - `pipe()`: For inter-process communication
  - `dup2()`: For file descriptor redirection
  - `execve()`: For command execution
  - `wait/waitpid()`: For process synchronization
- **File Operations**: `open()`, `close()`, `read()`, `write()`
- **Memory Management**: `malloc()`, `free()`
- **Custom Libft**: Personal implementation of standard library functions

## Setup Instructions

1. Clone the repository:
   ```
   git clone https://github.com/gtretiak/C_Pipex/pipex.git
   cd C_Pipex
   ```

2. Compile the project:
   ```
   make        # For mandatory part
   make bonus  # For bonus features
   ```

3. Run the program:
   ```
   # Basic usage
   ./pipex infile "cmd1" "cmd2" outfile
   
   # With multiple pipes (bonus)
   ./pipex infile "cmd1" "cmd2" "cmd3" outfile
   
   # With heredoc (bonus)
   ./pipex here_doc DELIMITER "cmd1" "cmd2" outfile
   ```

## Usage Examples

### Basic Example

```bash
# This command:
./pipex infile "grep hello" "wc -l" outfile

# Is equivalent to:
< infile grep hello | wc -l > outfile
```

### Multiple Pipes (Bonus)

```bash
# This command:
./pipex infile "grep hello" "sort" "uniq" outfile

# Is equivalent to:
< infile grep hello | sort | uniq > outfile
```

### Heredoc (Bonus)

```bash
# This command:
./pipex here_doc EOF "grep hello" "wc -l" outfile

# Is equivalent to:
grep hello << EOF | wc -l >> outfile
```

## 5 Practical Real-World Applications

### 1. Data Processing Pipelines
**Real-world importance:**
- Efficient ETL (Extract, Transform, Load) pipelines for processing large datasets can be created
- The principles of Pipex directly apply to building scalable data processing systems that pass information through transformation stages

### 2. Command-Line Tool Development
**Real-world importance:**
- The project is a foundation to creating complex CLI tools that chain operations together
- Configuration files might be processed through multiple validation and transformation steps
- Understanding pipe mechanisms helps in developing tools that integrate seamlessly with existing Unix utilities

### 3. Shell Implementation
**Real-world importance:**
- The core concepts in Pipex are exactly what's needed to understand and build shell interpreters
- Terminal emulators and command processors rely on these same principles
- Knowledge of how commands are executed and connected is essential for building secure command execution environments

### 4. Concurrent Processing Systems
**Real-world importance:**
- Microservice architectures use similar principles for service-to-service communication
- Stream processing systems apply the same data flow concepts at scale
- Understanding process isolation and communication is fundamental to designing robust concurrent systems

### 5. System Monitoring and Control
**Real-world importance:**
- Monitoring systems often need to capture output from various commands and process it
- System automation tools use command pipelines to collect information and take actions
- Real-time data processing systems in industrial control applications follow similar patterns of connected processes

## Conclusion

Pipex represents a fundamental exploration of how Unix systems handle process communication, a concept that remains at the core of modern operating systems and software architecture. Implementing this mechanism from scratch gives not only C programming proficiency but also a deep understanding of operating system principles.
Required in this project understanding of process management, inter-process communication, file descriptor manipulation, and resource management is directly applicable to systems programming, application development, DevOps, and any field requiring robust command-line tools or data processing pipelines, allowing debugging complex system issues, optimizing data flows, and designing efficient multi-process applications. 

Beyond the technical implementation, Pipex builds critical thinking skills by requiring to thoroughly handle edge cases, prevent resource leaks, and eventually create a robust solution that mirrors the behavior of core system functionality.
