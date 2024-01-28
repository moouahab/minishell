/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex00.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouahab <mohamed.ouahab1999@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 09:10:00 by moouahab          #+#    #+#             */
/*   Updated: 2024/01/28 13:23:20 by moouahab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// 2 processes 

// 1) child process should gererate random numbers 
//    sand them to the parent 
// 2) Parent is going to sum all the numbers and print the result

int main(int argc, char const *argv[])
{
    int fd[2];
    int pid;

    // attention a faire pipe avent le fork
    if (pipe(fd) == -1)
        return 2;

    pid = fork();
    if (pid == -1)
        return 1;
    // =====================================
    if (pid == 0)
    {
        int i;
        int n;
        int arr[10];

        close(fd[0]);
        srand(time(NULL));
        n = rand() % 10 + 1; // permet de genre de valeur aleratoire 
        i = 0;
        while (i < n)
        {
            arr[i] = rand() % 11;
            i++;
        }
        if (write(fd[1], &n, sizeof(int)) == -1)
        {
            perror("write n ");
            return 4;
        }
        if (write(fd[1], arr, sizeof(int *) * n) < 0)
            return 3;
        close(fd[1]);
    }
    // ===================================================
    else
    {
        // process parent
        int n;
        int arr[10];
        int sum = 0;
        
        // ferme le fd inutile 
        close(fd[1]);
        if (read(fd[0], &n, sizeof(int)) == -1)
            return 5;
        if (read(fd[0], arr, sizeof(int *) * n) == -1)
            return 6;
        close(fd[0]);

        for (int i = 0; i < n; i++)
        {
            sum += arr[i];
        }
        printf("The sum of arr is: %d\n", sum);
        wait(NULL); // ATTENT LA FIN DE ENFANTS 
    }
    
    return 0;
}
