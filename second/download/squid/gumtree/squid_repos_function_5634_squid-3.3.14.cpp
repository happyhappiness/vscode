int
DiskdIOStrategy::callback()
{
    diomsg M;
    int x;
    int retval = 0;

    if (away >= magic2) {
        ++diskd_stats.block_queue_len;
        retval = 1;
        /* We might not have anything to do, but our queue
         * is full.. */
    }

    if (diskd_stats.sent_count - diskd_stats.recv_count >
            diskd_stats.max_away) {
        diskd_stats.max_away = diskd_stats.sent_count - diskd_stats.recv_count;
    }

    while (1) {
#ifdef	ALWAYS_ZERO_BUFFERS
        memset(&M, '\0', sizeof(M));
#endif

        x = msgrcv(rmsgid, &M, diomsg::msg_snd_rcv_sz, 0, IPC_NOWAIT);

        if (x < 0)
            break;
        else if (x != diomsg::msg_snd_rcv_sz) {
            debugs(47, DBG_IMPORTANT, "storeDiskdDirCallback: msgget returns " << x);
            break;
        }

        ++diskd_stats.recv_count;
        --away;
        handle(&M);
        retval = 1;		/* Return that we've actually done some work */

        if (M.shm_offset > -1)
            shm.put ((off_t) M.shm_offset);
    }

    return retval;
}