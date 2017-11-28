        fatal("shmat failed");
    }

    inuse_map = (char *)xcalloc((nbufs + 7) / 8, 1);
    diskd_stats.shmbuf_count += nbufs;

    for (int i = 0; i < nbufs; ++i) {
        CBIT_SET(inuse_map, i);
        put (i * SHMBUF_BLKSZ);
    }
}

void
DiskdIOStrategy::unlinkDone(diomsg * M)
{
    debugs(79, 3, "storeDiskdUnlinkDone: file " << shm.buf + M->shm_offset << " status " << M->status);
    ++statCounter.syscalls.disk.unlinks;

    if (M->status < 0)
        ++diskd_stats.unlink.fail;
    else
        ++diskd_stats.unlink.success;
}

void
DiskdIOStrategy::handle(diomsg * M)
{
    if (!cbdataReferenceValid (M->callback_data)) {
