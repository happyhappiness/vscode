void accept_mutex_on()
{
    struct sembuf op;

#ifdef NO_SEM_UNDO
    if (sigprocmask(SIG_BLOCK, &accept_block_mask, &accept_previous_mask)) {
        perror("sigprocmask(SIG_BLOCK)");
        exit (1);
    }
    op.sem_flg = 0;
#else
    op.sem_flg = SEM_UNDO;
#endif
    op.sem_num = 0;
    op.sem_op  = -1;
    if (semop(sem_id, &op, 1) < 0) {
        perror ("accept_mutex_on");
        exit (1);
    }
}