# Development Notes

This needs to as 1:1 as possible to the [original norminette](https://github.com/42school/norminette) tool written in python - some parts can be written to fit the c structure and if there is a more efficient route to do a task.

Arguments being parsed will be hard written for simplicity of not needing an argument library. arguments should only be parsed in one function to make sure the arguments are fully captured

a difference between the use of `content` and `source` variables from python to c, in python it stores strings of text, in c it stores a filedescriptor of a file whether it be a user made file or a temporarily made file from the `--[c/h]file` flags.