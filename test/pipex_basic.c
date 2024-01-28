/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouahab <mohamed.ouahab1999@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:23:33 by moouahab          #+#    #+#             */
/*   Updated: 2024/01/28 15:40:09 by moouahab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


/**
 * [Explication du fonctionnement de la simulation de commandes simultanées]
 * 
 * Pour pouvoir simuler des commandes simultanément, nous aurons
 * besoin de créer un processus par commande. Chaque processus
 * correspond à l'exécution d'une commande spécifique.
 * 
 * [Fonctionnement de la simulation par processus]
 * 
 * -    Chaque commande agit de manière indépendante des autres une
 *      fois que son processus est créé. Cela permet une exécution
 *      parallèle des commandes.
 * 
 * -    Une fois qu'un processus a terminé son exécution, sa sortie
 *      standard est redirigée vers l'entrée standard du processus suivant.
 *      Cette redirection est effectuée à l'aide de tubes (pipes),
 *      permettant ainsi un transfert continu de données entre les processus.
 * 
 * -    Chaque commande peut agir sur ses propres données et n'a pas besoin
 *      de connaître l'existence des autres processus pour fonctionner
 *      correctement. Cela garantit une exécution isolée et autonome de
 *      chaque commande.
 * 
 * -    La dernière commande, une fois que toutes les autres ont terminé
 *      leur exécution, prend en charge l'impression des résultats finaux.
 *      Elle collecte les données de sortie des commandes précédentes et
 *      les affiche à l'utilisateur.
 * 
 * [Avantages de cette approche]
 * 
 * -    L'utilisation de processus distincts pour chaque commande permet
 *      une gestion efficace des ressources système et une utilisation
 *      optimale du parallélisme pour accélérer l'exécution des commandes.
 * 
 * -    La séparation des processus garantit également une meilleure
 *      isolation des tâches, réduisant ainsi les risques d'interférence
 *      ou de conflits entre les différentes commandes.
 * 
 * -    Cette approche est conforme au modèle de communication
 *      inter-processus Unix, offrant une solution robuste et
 *      éprouvée pour la gestion des commandes simultanées dans
 *      un environnement programmable.
 * 
 */

int main(int argc, char const *argv[])
{
    int pfd[2];
    int id;
    int id2;
    
    if (pipe(pfd) == -1)
        return 1;

    /**
     * PARTIE 1: Création du premier enfant
     * 
     * Dans cette partie, nous créons un processus enfant pour exécuter la commande ping
     * et rediriger sa sortie standard vers l'entrée du tube (pipe).
     * 
     * Étapes :
     * 1.   Fermer l'extrémité de lecture du tube, car nous n'en avons pas
     *      besoin dans ce processus.
     * 
     * 2.   Utiliser dup2 pour rediriger la sortie standard (STDOUT_FILENO)
     *      vers le descripteur d'écriture du tube.
     * 
     * 3.   Fermer l'extrémité de lecture du tube, car nous avons déjà redirigé 
     *      la sortie standard.
     * 
     * 4.   Exécuter la commande ping en remplaçant le processus enfant par
     *      le programme ping. ping -c 5 google.com envoie cinq paquets à
     *      google.com.
     */
    id = fork();
    if (id == -1)
        return 2;
    if (id == 0)
    {
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
   /**
     * PARTIE 2: Création du deuxième enfant
     * 
     * Dans cette partie, nous créons un deuxième processus enfant pour lire 
     * la sortie standard de la commande ping et filtrer les lignes contenant 
     * "rtt" à l'aide de la commande grep.
     * 
     * Étapes :
     * 1.   Fermer l'extrémité d'écriture du tube, car nous n'en avons pas
     *      besoin dans ce processus.
     * 
     * 2.   Utiliser dup2 pour rediriger l'entrée standard (STDIN_FILENO)
     *      vers le descripteur de lecture du tube.
     * 
     * 3.   Fermer l'extrémité de lecture du tube, car nous avons déjà redirigé
     *      l'entrée standard.
     * 
     * 4.   Exécuter la commande grep pour rechercher les lignes contenant
     *      "rtt" dans la sortie de ping.
     */
    id2 = fork();
    if (id2 == -1)
        return 3;
    if (id2 == 0)
    {
        close(pfd[1]);
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        execlp("grep", "grep", "rtt", NULL);
    }
    /**
     * Une fois que tous les processus ont terminé leur exécution,
     * il est essentiel de fermer chaque descripteur de fichier (file descriptor)
     * associé aux tubes (pipes) et d'attendre la fin de l'exécution de chaque
     * processus enfant.
     * 
     * Fermeture des descripteurs de fichiers :
     * 
     * - close(pfd[1]): Ferme l'extrémité d'écriture du tube.
     *                  Cette étape est nécessaire pour indiquer à
     *                  tout processus lisant depuis le tube qu'il n'y
     *                  a plus de données à lire. Cela évite les fuites
     *                  de ressources et assure une gestion correcte des tubes.
     * 
     * - close(pfd[0]) : Ferme l'extrémité de lecture du tube. Cela libère les
     *                  ressources associées au descripteur de fichier et signale
     *                  à tout processus écrivant dans le tube que l'écriture est
     *                  terminée. Cela évite également les fuites de ressources
     *                  et garantit une fermeture propre des tubes.
     * 
     * Attente de la fin de l'exécution des processus enfants :
     * 
     * - waitpid(id, NULL, 0) : Attend la fin de l'exécution du premier
     *                          processus enfant identifié par son ID.
     *                          La fonction waitpid() permet au processus
     *                          parent d'attendre la fin de l'exécution
     *                          d'un processus enfant spécifique avant de
     *                          continuer son exécution. Cela assure que les
     *                          ressources associées au processus enfant sont
     *                          libérées une fois qu'il a terminé son exécution.
     * 
     * - waitpid(id2, NULL, 0): Attend la fin de l'exécution du deuxième
     *                          processus enfant identifié par son ID.
     *                          Cette étape garantit que tous les processus
     *                          enfants ont terminé leur exécution avant
     *                          que le processus parent ne se termine,
     *                          évitant ainsi les fuites de ressources et
     *                          les comportements inattendus. Cela assure 
     *                          également que toutes les opérations 
     *                          impliquant les processus enfants sont
     *                          complètes avant que le programme principal
     *                          ne se termine.
     * 
     */
    close(pfd[1]);
    close(pfd[0]);
    waitpid(id, NULL, 0);
    waitpid(id2, NULL, 0);

    return 0;
}



/**
 * [FONCTION] : waitpid(pid_t pid, int *status, int options)
 * 
 * @param pid : L'identifiant du processus que le processus parent doit attendre.
 * 
 * @param status : Un pointeur vers un entier où les informations sur le statut
 *                 du processus fils seront stockées.
 * 
 * @param options : Un ensemble d'indicateurs qui contrôlent le comportement 
 *                  de la fonction waitpid().
 * 
 * @return L'identifiant du processus fils si tout se déroule correctement.
 * @return -1 en cas d'erreur.
 * 
 * [DESCRIPTION]
 * 
 * La fonction waitpid() permet au processus parent de spécifier sur 
 * quel processus enfant il doit surveiller les changements d'état. 
 * 
 * Elle bloque l'exécution du processus parent jusqu'à ce que le processus
 * fils spécifié change d'état.
 * Les différents indicateurs dans 'options' contrôlent le comportement 
 * de la fonction.
 */
