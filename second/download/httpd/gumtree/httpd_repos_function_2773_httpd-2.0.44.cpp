static void proc_mutex_fcntl_setup(void)
{
    proc_mutex_lock_it.l_whence = SEEK_SET;   /* from current point */
    proc_mutex_lock_it.l_start = 0;           /* -"- */
    proc_mutex_lock_it.l_len = 0;             /* until end of file */
    proc_mutex_lock_it.l_type = F_WRLCK;      /* set exclusive/write lock */
    proc_mutex_lock_it.l_pid = 0;             /* pid not actually interesting */
    proc_mutex_unlock_it.l_whence = SEEK_SET; /* from current point */
    proc_mutex_unlock_it.l_start = 0;         /* -"- */
    proc_mutex_unlock_it.l_len = 0;           /* until end of file */
    proc_mutex_unlock_it.l_type = F_UNLCK;    /* set exclusive/write lock */
    proc_mutex_unlock_it.l_pid = 0;           /* pid not actually interesting */
}