void accept_mutex_init(void)
{
#ifdef NEED_UNION_SEMUN
    /* believe it or not, you need to define this under solaris */
    union semun {
        int val;
        struct semid_ds *buf;
        ushort *array;
    };
#endif

    union semun ick;

    sem_id = semget(999, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
       perror ("semget");
       exit (1);
    }
    ick.val = 1;
    if (semctl(sem_id, 0, SETVAL, ick) < 0) {
       perror ("semctl");
        exit(1);
    }
#ifdef NO_SEM_UNDO
    sigfillset(&accept_block_mask);
    sigdelset(&accept_block_mask, SIGHUP);
    sigdelset(&accept_block_mask, SIGTERM);
    sigdelset(&accept_block_mask, SIGUSR1);
#endif
}