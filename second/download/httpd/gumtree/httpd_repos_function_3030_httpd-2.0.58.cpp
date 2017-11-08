static void avoid_zombies(int signo)
{
    int exit_status;

    while (waitpid(-1, &exit_status, WNOHANG) > 0) {
        /* do nothing */
    }
}