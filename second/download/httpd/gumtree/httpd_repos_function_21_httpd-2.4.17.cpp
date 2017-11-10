static void *get_shared_mem(apr_size_t size)
{
    key_t shmkey = IPC_PRIVATE;
    int shmid = -1;
    void *result;
#ifdef MOVEBREAK
    char *obrk;
#endif

    if ((shmid = shmget(shmkey, size, IPC_CREAT | SHM_R | SHM_W)) == -1) {
        perror("shmget");
        exit(1);
    }

#ifdef MOVEBREAK
    /*
     * Some SysV systems place the shared segment WAY too close
     * to the dynamic memory break point (sbrk(0)). This severely
     * limits the use of malloc/sbrk in the program since sbrk will
     * refuse to move past that point.
     *
     * To get around this, we move the break point "way up there",
     * attach the segment and then move break back down. Ugly
     */
    if ((obrk = sbrk(MOVEBREAK)) == (char *) -1) {
        perror("sbrk");
    }
#endif

#define BADSHMAT  ((void *)(-1))
    if ((result = shmat(shmid, 0, 0)) == BADSHMAT) {
        perror("shmat");
    }
    /*
     * We must avoid leaving segments in the kernel's
     * (small) tables.
     */
    if (shmctl(shmid, IPC_RMID, NULL) != 0) {
        perror("shmctl(IPC_RMID)");
    }
    if (result == BADSHMAT)  /* now bailout */
        exit(1);

#ifdef MOVEBREAK
    if (obrk == (char *) -1)
        return;  /* nothing else to do */
    if (sbrk(-(MOVEBREAK)) == (char *) -1) {
        perror("sbrk 2");
    }
#endif
    return result;
}