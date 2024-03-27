
# Minishell

Welcome to the Minishell project! Minishell is a Bash replica compliant with POSIX standards, developed in the C language. This project, carried out in collaboration with [@rabenoit](https://github.com/rabenoit),  aims to provide a lightweight and versatile command-line interface for Unix and Unix-like system users.

## Objectif du Projet

The main objective of Minishell is to provide a lightweight and efficient alternative to Bash, focusing on POSIX compliance. Unlike more complex shell interpreters, Minishell concentrates on the essentials, offering an intuitive user interface and essential features for file manipulation, process management, and filesystem navigation tasks.

## Fonctionnalités Principales

- Command interpretation in accordance with POSIX standards.
- Management of environment variables.
- Execution of internal and external commands.
- Stream redirection (standard input/output, file redirections).
- Background and foreground process management.
- Metacharacter expansion (globbing).
- Command history and search functionalities.

## Structure de la Documentation

This documentation is designed to guide you through the installation, configuration, and usage of Minishell. It is organized to provide detailed information on every aspect of the project, including features, configuration options, and usage examples.

We encourage you to explore this documentation to fully utilize Minishell's capabilities and contribute to its continuous development.

Feel free to contact [@rabenoit](https://github.com/rabenoit) or myself if you have any questions, feedback, or if you wish to contribute to the project.

## Documentation

The first step in building the project is to correctly handle user input. To achieve this, we have implemented tokenization following the grammar of [bash --posix](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)  Alongside the lexer creation, we also handle syntax errors.
```
minishell$ ls | cat -e |  head -n 5 | wc -l > out
tokenisation : cmd pipe cmd arg pipe cmd arg arg pipe cmd arg redierction file
```
Once tokenization is correctly handled, we move on to the expansion stage, which involves processing environment variables. Two essential elements to consider are setting up the environment and detecting escape sequences, whether in single or double-quoted strings.

#### Mise place de l'environnement

We decided to build the environment with a linked list of key/value pairs. 

```c
typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *env;
}                   t_env;
```
We find this much easier to manipulate.

#### Détection des quote

Quote detection will occur during tokenization. There will be a function indicating whether the word appears as a substring or not. It's important to determine if the token between quotes should be joined with other tokens or not.

```c
char	*get_quoted_word(char *input, size_t *i, char quote)
{
	char	*word;
	size_t	j;
	size_t	len;

	(*i)++;
	len = ft_strlen_c(input + *i, quote);
	if (len == 0)
	{
		(*i)++;
		return (NULL);
	}
	word = ft_calloc(sizeof(char), len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (input[*i] && j < len)
		word[j++] = input[(*i)++];
	word[j] = '\0';
	(*i)++;
	return (word);
}

int	get_next_word(char *input, size_t *i, t_word **words)
{
	char	*word;

	if (is_quote(input[*i]))
		word = get_quoted_word(input, i, input[*i]);
	else if (is_operator(input[*i]))
	{
		word = get_operator_word(input, i);
		return (add_word(words, word, get_operator_token(word)));
	}
	else
		word = get_word(input, i);
	if (!word)
		return (EXIT_FAILURE);
	if (*i > ft_strlen(input))
		return (EXIT_FAILURE);
	while (*i < ft_strlen(input))
	{
		if (is_quote(input[*i]))
			word = ft_strjoin(word, get_quoted_word(input, i, input[*i]));
		else if (!is_operator(input[*i]) && !is_whitespace(input[*i]))
			word = ft_strjoin(word, get_word(input, i));
		else
			break ;
	}
	return (add_word(words, word, WORD));
}

```
#### Expand 

If an environment variable is found alone or within quotes, then we have to look up the key in the environment and replace the token with its value. However, if it's inside single quotes, we do nothing.

```
minishell$  '$PATH'$HOME "$USER"
minishell$  $PATH/home/moouahab moouahab
```
### Execution 

The execution process retrieves the already processed tokenization. It stores all commands along with their arguments, paths, file descriptors, and other relevant information in a linked list.

```
typedef struct s_cmd
{
	char			**av;
	char			*path;
	int				fdout;
	int				fdin;
	char			*filein;
	t_token			typein;
	t_token			typeout;
	size_t			i;
	struct s_cmd	*next;
}					t_cmd;

```

#### Mise en place des pipe 

Setting up Pipes
When executing a command in a shell, whether it's a single command or a series of commands, each command requires an input file descriptor to read the data to be processed. But what happens when there are multiple commands to execute? The solution lies in implementing a feature called "multipipe," which efficiently manages multiple commands simultaneously. This functionality is made possible through multiprocess programming in the C language.

To understand how multipipe works, it's essential to grasp the concept of processes in computer science. A process can be seen as a running instance of a program. When we execute a command in a shell, a process is created to execute that command. With multipipe, we can create multiple processes, one for each command to execute, and have them communicate with each other via "pipes."

A "pipe" is a communication mechanism that allows the standard output of one process to be connected to the standard input of another process. Thus, the data produced by one command can be transmitted to another command for processing without requiring temporary files.

Implementing multipipe involves creating a pipeline of processes, where the standard output of each process is redirected to the standard input of the next process using pipes. This allows for chaining the execution of multiple commands seamlessly, as if they were executed sequentially.

```
void	pipe_manager(t_shell *shell, size_t i)
{
	if (!shell->pfd)
		return ;
	if (i > 0)
	{
		if (dup2(shell->pfd[i - 1][0], STDIN_FILENO) == -1)
			perror("dup2");
		close(shell->pfd[i - 1][1]);
	}
	if (i < shell->pipe_count)
	{
		if (dup2(shell->pfd[i][1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(shell->pfd[i][0]);
	}
	free_pipes(shell->pfd, shell->pipe_count);
}
```
##### Here's an example of using pipes in Minishell:

```
minishell$ ls -l | grep .txt | wc -l

```
This command lists all files in the current directory, passes the output through grep to filter only the files with ".txt" extension, and then counts the number of lines.


In addition to managing multiple commands concurrently through multipipes, Minishell also handles input and output redirections. Redirections allow the input or output of a command to be redirected to or from a file instead of the standard input (stdin) or standard output (stdout). Here's an explanation of how redirections work in Minishell:

- Output Redirection (>): The > symbol is used to redirect the standard output of a command to a file. When a command is followed by >, Minishell opens (or creates if it doesn't exist) the specified file and directs the output of the command to that file, overwriting its contents if the file already exists.

Example:

```bash
minishell$ echo "Hello, world!" > output.txt
This command writes "Hello, world!" to a file named output.txt.
```
- Append Redirection (>>): The >> symbol is used to append the standard output of a command to a file. Similar to >, but instead of overwriting the file, >> appends the output to the end of the file.

Example:

```bash
minishell$ echo "Second line" >> output.txt
This command appends "Second line" to the existing output.txt file.
```
- Input Redirection (<): The < symbol is used to redirect the standard input of a command from a file instead of the keyboard. When a command is followed by <, Minishell reads input from the specified file instead of waiting for keyboard input.

Example:

```bash
minishell$ cat < input.txt
This command reads the contents of the input.txt file and outputs them to the terminal using cat.
```


- Here Document (<<): The << symbol allows multiple lines of input to be passed to a command. It is used to specify a "here document," which is a way of providing input to a command inline within the shell script.

Example:
```bash
minishell$ cat << EOF
> Line 1
> Line 2
> EOF
```
This command uses a here document to provide input to cat, which then outputs the specified lines.

Minishell handles these redirections by modifying the file descriptors associated with the standard input and output of the commands accordingly. It ensures that the output of a command is directed to the specified file or that input is read from the specified file as needed, providing flexibility and versatility in command execution.





## Authors

- [@rabenoit](https://github.com/rabenoit)
- [@moouahab](https://github.com/moouahab)
