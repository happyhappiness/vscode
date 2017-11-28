void
SharedMemory::init(int ikey, int magic2)
{
    nbufs = (int)(magic2 * 1.3);
    id = shmget((key_t) (ikey + 2),
                nbufs * SHMBUF_BLKSZ, 0600 | IPC_CREAT);

    if (id < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "shmget: " << xstrerr(xerrno));
        fatal("shmget failed");
    }

    buf = (char *)shmat(id, NULL, 0);

    if (buf == (void *) -1) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "shmat: " << xstrerr(xerrno));
        fatal("shmat failed");
    }

    inuse_map = (char *)xcalloc((nbufs + 7) / 8, 1);
    diskd_stats.shmbuf_count += nbufs;

    for (int i = 0; i < nbufs; ++i) {
        CBIT_SET(inuse_map, i);
        put (i * SHMBUF_BLKSZ);
    }
}