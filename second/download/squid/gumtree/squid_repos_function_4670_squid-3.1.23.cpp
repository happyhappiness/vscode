void
UFSCleanLog::write(StoreEntry const &e)
{
    StoreSwapLogData s;
    static size_t ss = sizeof(StoreSwapLogData);
    s.op = (char) SWAP_LOG_ADD;
    s.swap_filen = e.swap_filen;
    s.timestamp = e.timestamp;
    s.lastref = e.lastref;
    s.expires = e.expires;
    s.lastmod = e.lastmod;
    s.swap_file_sz = e.swap_file_sz;
    s.refcount = e.refcount;
    s.flags = e.flags;
    xmemcpy(&s.key, e.key, SQUID_MD5_DIGEST_LENGTH);
    xmemcpy(outbuf + outbuf_offset, &s, ss);
    outbuf_offset += ss;
    /* buffered write */

    if (outbuf_offset + ss >= CLEAN_BUF_SZ) {
        if (FD_WRITE_METHOD(fd, outbuf, outbuf_offset) < 0) {
            /* XXX This error handling should probably move up to the caller */
            debugs(50, 0, "storeDirWriteCleanLogs: " << newLog << ": write: " << xstrerror());
            debugs(50, 0, "storeDirWriteCleanLogs: Current swap logfile not replaced.");
            file_close(fd);
            fd = -1;
            unlink(newLog);
            sd->cleanLog = NULL;
            delete this;
            return;
        }

        outbuf_offset = 0;
    }
}