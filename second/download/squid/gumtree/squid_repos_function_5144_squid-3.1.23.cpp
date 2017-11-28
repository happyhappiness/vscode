void
DiskdIOStrategy::unlinkFile(char const *path)
{
    if (shedLoad()) {
        /* Damn, we need to issue a sync unlink here :( */
        debugs(79, 2, "storeDiskUnlink: Out of queue space, sync unlink");
#if USE_UNLINKD

        unlinkdUnlink(path);
#else

        unlink(path);
#endif

        return;
    }

    /* We can attempt a diskd unlink */
    int x;

    ssize_t shm_offset;

    char *buf;

    buf = (char *)shm.get(&shm_offset);

    xstrncpy(buf, path, SHMBUF_BLKSZ);

    x = send(_MQD_UNLINK,
             0,
             (StoreIOState::Pointer )NULL,
             0,
             0,
             shm_offset);

    if (x < 0) {
        debugs(79, 1, "storeDiskdSend UNLINK: " << xstrerror());
        ::unlink(buf);		/* XXX EWW! */
        //        shm.put (shm_offset);
    }

    diskd_stats.unlink.ops++;
}