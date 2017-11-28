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