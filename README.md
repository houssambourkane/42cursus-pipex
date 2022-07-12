# Pipex
This project aims provide an inter-process communication (IPC) between two processes, by creating pipes that will redirect the output of the current command to the input of the next command
### Steps to use it :
#### 1. Clone the repository
```
git clone https://github.com/houssambourkane/42cursus-pipex.git pipex
```
#### 2. Access the mandatory directory (bonus is for heredoc and multiple commands)
```
cd pipex/mandatory
```
#### 3. Run the Makefile command
```
make all
```
#### 4. It will generate the executable of the program, that takes 5 arguments excluding the executable
```
Syntax :
./pipex filename1 command1 command2 filename2
 ```
 > This program actually reads the input from the __filename1__, execute the __command1__ to this input, and redirect the output to the __command2__ through the pipe, then execute the __command2__ to the input sent by the pipe, and redirects the final output to __filename2__
 ## Examples
 ### Without options
 ```
./pipex file1 cat sort file2
 ```
 - *Equivalent to < file1 cat | sort > file2*
  ### With options
  ```
./pipex file1 "ls -l" "sort -r" file2
 ```
  - *Equivalent to < file1  ls -l | sort -r > file2*
 > File1 must exists, while file2 will be automatically created
