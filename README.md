# Pipex

Implement UNIX piping with C language.

## [Mandatory]
```
$ ./pipex input_file cmd_1 cmd_2 output_file
```
The execution of above program works same as below shell command.
```
$ < input_file cmd_1 | cmd_2 > output_file
```

## [Bonus]
- Handle multiple pipes.
```
$ ./pipex input_file cmd_1 cmd_2 cmd_3 ... cmd_n output_file

Above program is equal to below shell command.
$ < input_file cmd_1 | cmd_2 | cmd_3 ... | cmd_n > output_file
```
- Support << and >> when the first parameter is "here_doc".
```
$ ./pipex here_doc LIMITER cmd_1 cmd_2 output_file
Above program is equal to below shell command.
$ cmd_1 << LIMITER | cmd_2 >> output_file
```

# Usage
```
>> Mandatory <<
$ make
$ ./pipex input.txt cat wc output.txt

>> Bonus <<
$ make bonus

// Multiple pipes
$ ./pipex input.txt cat wc ... output.txt

// << and >> when the first param is "here_doc"
$ ./pipex here_doc STOP cat wc output.txt
... your input from stdin ...
STOP
```
