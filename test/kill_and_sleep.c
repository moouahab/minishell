/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_and_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouahab <mohamed.ouahab1999@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 08:28:02 by moouahab          #+#    #+#             */
/*   Updated: 2024/01/28 09:08:57 by moouahab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/**
 * La fonction usleep() suspend temporairement l'exécution du programme pendant
 * un certain nombre de microsecondes spécifié.
 * 
 * Paramètre :
 *   - usec : Le nombre de microsecondes pendant lesquelles le programme sera suspendu.
 * 
 * Retour :
 *   - Retourne 0 en cas de succès.
 *   - Retourne 1 en cas d'erreur.
 * 
*/


/**
 * La fonction kill(pid, signal) permet d'envoyer un signal à un processus en cours d'exécution.
 * 
 * Paramètres :
 *   - pid : Le PID (identifiant de processus) du processus auquel envoyer le signal.
 *   - signal : Le signal à envoyer au processus spécifié.
 * 
 * Retour :
 *   - Retourne 0 en cas de succès.
 *   - Retourne -1 en cas d'erreur.
 * 
*/


/**
 * Ce programme crée un processus enfant qui boucle indéfiniment.
 * À chaque itération de la boucle, l'enfant effectue un printf et attend pendant
 * un certain nombre de microsecondes spécifié avec usleep().
 * 
 * Dans le processus parent, il dort pendant 1 seconde, puis envoie un signal pour tuer l'enfant.
 * Ensuite, le processus principal attend la fin du processus enfant.
 */



int main(int argc, char const *argv[])
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        return 1;
    if (pid == 0)
    {
        while (1)
        {
            printf("Some text goes here\n");
            if (usleep(60000) == -1)
            {
                perror("la function usleep a eu un promblem");
            }
        }       
    }
    else
    {
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL); // fait attendre tout les enfants 
    }
    return 0;
}
