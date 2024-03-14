/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:17:09 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/14 17:05:35 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
	t_data d;

	if (argc >= 5)
	{
		init_data(argc, argv, envp, &d);
		pipe_commands(&d);
	}
}

void	init_data(int argc, char *argv[], char *envp[], t_data *d)
{
	init_data_null(&d);
	init_file_val(argc, argv, &d);
	init_cmd_data(argv, envp, &d);
	print_all(d);
	// free_all(d);
	// print_all(d);
}

#define BUFFER_SIZE 4096

void	pipe_commands(t_data *d)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Fork a child process
    d->pid[0] = fork();
    if (d->pid[0] == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Child process
    if (d->pid[0] == 0)
    {
        printf("hello form 1st child\n");

        close(d->pip[0][READ]);
        if (dup2(d->pip[0][WRITE], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(d->pip[0][WRITE]);

        // Call the desired Linux command using execve
        char *args[] = {d->cmd[0], d->cmd_arg[0], NULL}; 
		// Example: list files in the current directory
        if (execve(d->cmd_path[0], args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else // next child process
    { 
        printf("hello form 2nd child\n");
        // Fork a child process
        d->pid[1] = fork();
        if (d->pid[1] == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
        }
            // Child process
        if (d->pid[1] == 0)
        {
            close(d->pip[0][WRITE]);
            if (dup2(d->pip[0][READ], STDIN_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(d->pip[0][READ]);
            close(d->pip[1][READ]);
            if (dup2(d->pip[1][WRITE], STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(d->pip[1][WRITE]);
            char *args2[] = {d->cmd[1], d->cmd_arg[1], NULL}; 
            if (execve(d->cmd_path[1], args2, NULL) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
         }
        else
        { // next child process
            close(d->pip[0][READ]);
            close(d->pip[0][WRITE]);
            close(d->pip[1][WRITE]);
            waitpid(d->pid[0], NULL, 0);
            waitpid(d->pid[1], NULL, 0);
            printf("hello form parent\n");

            // Open or create a file for writing
            int fd = open(d->out_fl, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            // Read from the read end of the pipe and write to the file
            while ((bytes_read = read(d->pip[1][READ], buffer, BUFFER_SIZE)) > 0) {
                if (write(fd, buffer, bytes_read) != bytes_read) {
                    perror("write");
                    exit(EXIT_FAILURE);
                }
            }

            if (bytes_read == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            // Close the file descriptor and the read end of the pipe
            close(fd);
            close(d->pip[1][READ]);
        }
    }
}