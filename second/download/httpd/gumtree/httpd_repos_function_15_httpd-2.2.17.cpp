void accept_mutex_on()
{
    if (sigprocmask(SIG_BLOCK, &accept_block_mask, &accept_previous_mask)) {
        perror("sigprocmask(SIG_BLOCK)");
        exit (1);
    }
    if (pthread_mutex_lock (mutex)) {
        perror ("pthread_mutex_lock");
        exit (1);
    }
}