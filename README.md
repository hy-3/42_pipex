# Pipex

It's a program which acts as UNIX piping.

## [Mandatory]
```
$ ./pipex input_file cmd_1 cmd_2 output_file

The execution of above program works same as below shell command.
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
$ ./pipex here_doc LIMIT_STRING cmd_1 cmd_2 output_file

Above program is equal to below shell command.
$ cmd_1 << LIMIT_STRING | cmd_2 >> output_file
```

# Usage
```
[Mandatory]
$ make

(Before running the below commands, you need to create input.txt with any content to pass the content of it to cmd_1.)
ex 1) $ ./pipex input.txt cat wc output.txt
ex 2) $ ./pipex input.txt cat "wc -l" output.txt

[Bonus]
$ make bonus
(If the above command returns `make: Nothing to be done for `bonus'.`, run a below command.)
$ make re_bonus

(Before running the below commands, you need to create input.txt with any contnet to pass the content of it to cmd_1.)
// Multiple pipes
ex 1) $ ./pipex input.txt cat "grep a" wc output.txt
ex 2) $ ./pipex input.txt cat wc ls date output.txt

// << and >> when the first param is "here_doc"
ex 1) $ ./pipex here_doc END cat wc output.txt
... you can type anything you want
... you can type anything you want
END (<- this is an arbitrary string which you choose when you run the above program.)
```
