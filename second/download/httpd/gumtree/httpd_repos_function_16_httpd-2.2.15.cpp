void accept_mutex_off()
{
    if (pthread_mutex_unlock (mutex)) {
        perror ("pthread_mutex_unlock");
        exit (1);
    }
    if (sigprocmask(SIG_SETMASK, &accept_previous_mask, NULL)) {
        perror("sigprocmask(SIG_SETMASK)");
        exit (1);
    }
}