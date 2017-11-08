void accept_mutex_off()
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op  = 1;
#ifdef NO_SEM_UNDO
    op.sem_flg = 0;
#else
    op.sem_flg = SEM_UNDO;
#endif
    if (semop(sem_id, &op, 1) < 0) {
        perror ("accept_mutex_off");
        exit (1);
    }
#ifdef NO_SEM_UNDO
    if (sigprocmask(SIG_SETMASK, &accept_previous_mask, NULL)) {
        perror("sigprocmask(SIG_SETMASK)");
        exit (1);
    }
#endif
}