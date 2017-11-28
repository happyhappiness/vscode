void
CossCleanLog::write(StoreEntry const &e)
{
    CossCleanLog *state = this;
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
    memcpy(&s.key, e.key, SQUID_MD5_DIGEST_LENGTH);
    memcpy(outbuf + outbuf_offset, &s, ss);
    outbuf_offset += ss;
    /* buffered write */

    if (outbuf_offset + ss > CLEAN_BUF_SZ) {
        if (FD_WRITE_METHOD(fd, outbuf, outbuf_offset) < 0) {
            debugs(50, DBG_CRITICAL, "storeCossDirWriteCleanLogs: " << newLog << ": write: " << xstrerror());
            debugs(50, DBG_CRITICAL, "storeCossDirWriteCleanLogs: Current swap logfile not replaced.");
            file_close(fd);
            fd = -1;
            unlink(newLog);
            sd->cleanLog = NULL;
            delete state;
            return;
        }

        outbuf_offset = 0;
    }
}