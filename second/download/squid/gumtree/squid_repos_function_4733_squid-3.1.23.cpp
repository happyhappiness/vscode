void
RebuildState::rebuildFromDirectory()
{
    LOCAL_ARRAY(char, hdr_buf, SM_PAGE_SIZE);
    currentEntry(NULL);
    cache_key key[SQUID_MD5_DIGEST_LENGTH];

    struct stat sb;
    int swap_hdr_len;
    int fd = -1;
    StoreMeta *tlv_list;
    assert(this != NULL);
    debugs(47, 3, "commonUfsDirRebuildFromDirectory: DIR #" << sd->index);

    for (int count = 0; count < speed; count++) {
        assert(fd == -1);
        sfileno filn = 0;
        int size;
        fd = getNextFile(&filn, &size);

        if (fd == -2) {
            debugs(47, 1, "Done scanning " << sd->path << " swaplog (" << n_read << " entries)");
            _done = true;
            return;
        } else if (fd < 0) {
            continue;
        }

        assert(fd > -1);
        /* lets get file stats here */

        if (fstat(fd, &sb) < 0) {
            debugs(47, 1, "commonUfsDirRebuildFromDirectory: fstat(FD " << fd << "): " << xstrerror());
            file_close(fd);
            store_open_disk_fd--;
            fd = -1;
            continue;
        }

        if ((++counts.scancount & 0xFFFF) == 0)
            debugs(47, 3, "  " << sd->path  << " " << std::setw(7) << counts.scancount  << " files opened so far.");
        debugs(47, 9, "file_in: fd=" << fd  << " "<< std::setfill('0') << std::hex << std::uppercase << std::setw(8) << filn);


        statCounter.syscalls.disk.reads++;

        int len;

        if ((len = FD_READ_METHOD(fd, hdr_buf, SM_PAGE_SIZE)) < 0) {
            debugs(47, 1, "commonUfsDirRebuildFromDirectory: read(FD " << fd << "): " << xstrerror());
            file_close(fd);
            store_open_disk_fd--;
            fd = -1;
            continue;
        }

        file_close(fd);
        store_open_disk_fd--;
        fd = -1;
        swap_hdr_len = 0;

        StoreMetaUnpacker aBuilder(hdr_buf, len, &swap_hdr_len);

        if (!aBuilder.isBufferSane()) {
            debugs(47, 1, "commonUfsDirRebuildFromDirectory: Swap data buffer length is not sane.");
            /* XXX shouldn't this be a call to commonUfsUnlink ? */
            sd->unlinkFile ( filn);
            continue;
        }

        tlv_list = aBuilder.createStoreMeta ();

        if (tlv_list == NULL) {
            debugs(47, 1, "commonUfsDirRebuildFromDirectory: failed to get meta data");
            /* XXX shouldn't this be a call to commonUfsUnlink ? */
            sd->unlinkFile (filn);
            continue;
        }

        debugs(47, 3, "commonUfsDirRebuildFromDirectory: successful swap meta unpacking");
        memset(key, '\0', SQUID_MD5_DIGEST_LENGTH);

        StoreEntry tmpe;
        InitStoreEntry visitor(&tmpe, key);
        for_each(*tlv_list, visitor);
        storeSwapTLVFree(tlv_list);
        tlv_list = NULL;

        if (storeKeyNull(key)) {
            debugs(47, 1, "commonUfsDirRebuildFromDirectory: NULL key");
            sd->unlinkFile(filn);
            continue;
        }

        tmpe.key = key;
        /* check sizes */

        if (tmpe.swap_file_sz == 0) {
            tmpe.swap_file_sz = (uint64_t) sb.st_size;
        } else if (tmpe.swap_file_sz == (uint64_t)(sb.st_size - swap_hdr_len)) {
            tmpe.swap_file_sz = (uint64_t) sb.st_size;
        } else if (tmpe.swap_file_sz != (uint64_t)sb.st_size) {
            debugs(47, 1, "commonUfsDirRebuildFromDirectory: SIZE MISMATCH " <<
                   tmpe.swap_file_sz << "!=" <<
                   sb.st_size);

            sd->unlinkFile(filn);
            continue;
        }

        if (EBIT_TEST(tmpe.flags, KEY_PRIVATE)) {
            sd->unlinkFile(filn);
            counts.badflags++;
            continue;
        }

        /* this needs to become
         * 1) unpack url
         * 2) make synthetic request with headers ?? or otherwise search
         * for a matching object in the store
         * TODO FIXME change to new async api
         * TODO FIXME I think there is a race condition here with the
         * async api :
         * store A reads in object foo, searchs for it, and finds nothing.
         * store B reads in object foo, searchs for it, finds nothing.
         * store A gets called back with nothing, so registers the object
         * store B gets called back with nothing, so registers the object,
         * which will conflict when the in core index gets around to scanning
         * store B.
         *
         * this suggests that rather than searching for duplicates, the
         * index rebuild should just assume its the most recent accurate
         * store entry and whoever indexes the stores handles duplicates.
         */
        e = Store::Root().get(key);

        if (e && e->lastref >= tmpe.lastref) {
            /* key already exists, current entry is newer */
            /* keep old, ignore new */
            counts.dupcount++;
            continue;
        } else if (NULL != e) {
            /* URL already exists, this swapfile not being used */
            /* junk old, load new */
            e->release();	/* release old entry */
            counts.dupcount++;
        }

        counts.objcount++;
        // tmpe.dump(5);
        currentEntry(sd->addDiskRestore(key,
                                        filn,
                                        tmpe.swap_file_sz,
                                        tmpe.expires,
                                        tmpe.timestamp,
                                        tmpe.lastref,
                                        tmpe.lastmod,
                                        tmpe.refcount,	/* refcount */
                                        tmpe.flags,		/* flags */
                                        (int) flags.clean));
        storeDirSwapLog(currentEntry(), SWAP_LOG_ADD);
    }

}