int
DiskdIOStrategy::SEND(diomsg *M, int mtype, int id, size_t size, off_t offset, ssize_t shm_offset)
{
    static int send_errors = 0;
    static int last_seq_no = 0;
    static int seq_no = 0;
    int x;

    M->mtype = mtype;
    M->size = size;
    M->offset = offset;
    M->status = -1;
    M->shm_offset = (int) shm_offset;
    M->id = id;
    M->seq_no = ++seq_no;

    if (M->seq_no < last_seq_no)
        debugs(79, DBG_IMPORTANT, "WARNING: sequencing out of order");

    x = msgsnd(smsgid, M, diomsg::msg_snd_rcv_sz, IPC_NOWAIT);

    last_seq_no = M->seq_no;

    if (0 == x) {
        ++diskd_stats.sent_count;
        ++away;
    } else {
        debugs(79, DBG_IMPORTANT, "storeDiskdSend: msgsnd: " << xstrerror());
        cbdataReferenceDone(M->callback_data);
        ++send_errors;
        assert(send_errors < 100);
        if (shm_offset > -1)
            shm.put(shm_offset);
    }

    /*
     * We have to drain the queue here if necessary.  If we don't,
     * then we can have a lot of messages in the queue (probably
     * up to 2*magic1) and we can run out of shared memory buffers.
     */
    /*
     * Note that we call Store::Root().callbackk (for all SDs), rather
     * than callback for just this SD, so that while
     * we're "blocking" on this SD we can also handle callbacks
     * from other SDs that might be ready.
     */

    struct timeval delay = {0, 1};

    while (away > magic2) {
        select(0, NULL, NULL, NULL, &delay);
        Store::Root().callback();

        if (delay.tv_usec < 1000000)
            delay.tv_usec <<= 1;
    }

    return x;
}