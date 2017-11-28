void
Fs::Ufs::RebuildState::rebuildFromDirectory()
{
    cache_key key[SQUID_MD5_DIGEST_LENGTH];

    struct stat sb;
    int fd = -1;
    assert(this != NULL);
    debugs(47, 3, HERE << "DIR #" << sd->index);

    assert(fd == -1);
    sfileno filn = 0;
    int size;
    fd = getNextFile(&filn, &size);

    if (fd == -2) {
        debugs(47, DBG_IMPORTANT, "Done scanning " << sd->path << " dir (" <<
               n_read << " entries)");
        _done = true;
        return;
    } else if (fd < 0) {
        return;
    }

    assert(fd > -1);
    /* lets get file stats here */

    ++n_read;

    if (fstat(fd, &sb) < 0) {
        debugs(47, DBG_IMPORTANT, HERE << "fstat(FD " << fd << "): " << xstrerror());
        file_close(fd);
        --store_open_disk_fd;
        fd = -1;
        return;
    }

    MemBuf buf;
    buf.init(SM_PAGE_SIZE, SM_PAGE_SIZE);
    if (!storeRebuildLoadEntry(fd, sd->index, buf, counts))
        return;

    StoreEntry tmpe;
    const bool loaded = storeRebuildParseEntry(buf, tmpe, key, counts,
                        (int64_t)sb.st_size);

    file_close(fd);
    --store_open_disk_fd;
    fd = -1;

    if (!loaded) {
        // XXX: shouldn't this be a call to commonUfsUnlink?
        sd->unlinkFile(filn); // should we unlink in all failure cases?
        return;
    }

    if (!storeRebuildKeepEntry(tmpe, key, counts))
        return;

    ++counts.objcount;
    // tmpe.dump(5);
    currentEntry(sd->addDiskRestore(key,
                                    filn,
                                    tmpe.swap_file_sz,
                                    tmpe.expires,
                                    tmpe.timestamp,
                                    tmpe.lastref,
                                    tmpe.lastmod,
                                    tmpe.refcount,  /* refcount */
                                    tmpe.flags,     /* flags */
                                    (int) flags.clean));
    storeDirSwapLog(currentEntry(), SWAP_LOG_ADD);
}