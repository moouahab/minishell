/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouahab <mohamed.ouahab1999@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 14:52:28 by moouahab          #+#    #+#             */
/*   Updated: 2024/01/28 22:27:52 by moouahab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"



/**
 * [GESTIONS DES MULTIPIPE]
 * 
 * Etape 1: Creeation du reseau intre-process
 * 
 * 
 * 
*/

int main(int argc, char const *argv[], char *const *env)
{
    int pfd[NUM_CHILDREN - 1][2]; // Tableau pour stocker les descripteurs de fichiers des tubes
    int pid;
    int e;
    char *const ls[] = {"ls", NULL};
    char *const cat[] = {"cat", "-e", "main.c", NULL};
    char *const wc[] = {"wc", "-l", NULL};
    char *strs[] = {"/bin/ls", "/bin/cat", "/bin/wc"};

    char *const *const arr[] = {ls, cat, wc};
    /**
     * Etape 1: Création du réseau inter-processus
     * 
     * Pour créer plusieurs tubes (pipes), nous utilisons 
     * une boucle qui itère sur la création d'un tube
     * dans le tableau 'pfd'.
     * Chaque 'pfd[i]' représente un tube avec deux descripteurs de fichier :
     * - pfd[i][0] pour la lecture depuis le tube.
     * - pfd[i][1] pour l'écriture dans le tube.
     * 
     * Nous utilisons un tableau de tubes (pipes)
     * pour établir des connexions entre
     * les processus enfants. Comme chaque enfant
     * communique avec ses voisins, nous
     * aurons besoin de (NUM_CHILDREN - 1) tubes.
     */
    e = 0;
    while (e < NUM_CHILDREN - 1)
    {
        if (pipe(pfd[e]) == -1)
        {
            perror("pipe");
            return (1);
        }
        e++;
    }
    
    /**
     * Partie 2 : Création de multiples processus enfants
     * 
     * Pour créer plusieurs processus enfants successivement, nous utilisons une boucle
     * jusqu'à atteindre le nombre d'enfants souhaité.
     * 
     * Pour chaque enfant :
     * 
     *  - Si ce n'est pas le premier enfant, nous fermons le descripteur de fichier de lecture
     *    du tube précédent et redirigeons l'entrée standard (stdin) vers ce tube. Cela permet à
     *    l'enfant de lire les données provenant du processus précédent.
     * 
     *  - Si ce n'est pas le dernier enfant, nous fermons le descripteur de fichier de lecture
     *    du tube actuel et redirigeons la sortie standard (stdout) vers ce tube. Ainsi, les
     *    données produites par cet enfant seront transmises au processus suivant via le tube.
     * 
     *  - Pour chaque enfant, nous avons une commande à exécuter. Ces commandes peuvent être
     *    des exécutables ou des scripts, et chacune effectue une tâche spécifique.
     *    Nous utilisons la fonction execve() pour exécuter ces commandes. Cela remplace
     *    le programme actuel du processus enfant par le programme spécifié dans la commande.
     *    Les paramètres de execve() comprennent le chemin vers le programme à exécuter,
     *    un tableau d'arguments (y compris le nom du programme), et un tableau d'environnement.
     * 
     * Une fois que tous les processus enfants sont créés, ils fonctionnent de manière indépendante,
     * exécutant leurs commandes respectives et communiquant via les tubes. Lorsqu'un processus
     * enfant termine son exécution, son descripteur de fichier est automatiquement fermé.
     * 
     * Cette approche de création et de gestion des processus enfants permet une communication
     * efficace entre eux, ainsi que l'exécution simultanée de plusieurs tâches dans un programme.
    */
    e = 0;
    while (e < NUM_CHILDREN)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("pipe");
            return (2);
        }
        else if (pid == 0)
        {
            if (e > 0)
            {
                close(pfd[e - 1][1]);
                dup2(pfd[e - 1][0], STDIN_FILENO);
            }
            if (e < NUM_CHILDREN - 1)
            {
                close(pfd[e][0]);
                dup2(pfd[e][1], STDOUT_FILENO);   
            }
            // ATTENTION LA DERNIER VALEUR DOIT ETRE A NULL C'EST OBLIGER 
            
            execve(strs[e], arr[e], env);
            perror("excve ne peut excuter");
            exit(EXIT_FAILURE);
        }
        
        e++;
    }
    e = 0;
    while (e < NUM_CHILDREN - 1)
    {
        close(pfd[e][0]);
        close(pfd[e][1]);
        e++;
    }
    while (wait(NULL) != -1)
        ;
       
    exit(EXIT_SUCCESS);
}
