void
Fs::Ufs::UFSSwapDir::logEntry(const StoreEntry & e, int op) const
{
    if (swaplog_fd < 0) {
        debugs(36, 5, "cannot log " << e << " in the middle of reconfiguration");
        return;
    }

    StoreSwapLogData *s = new StoreSwapLogData;
    s->op = (char) op;
    s->swap_filen = e.swap_filen;
    s->timestamp = e.timestamp;
    s->lastref = e.lastref;
    s->expires = e.expires;
    s->lastmod = e.lastModified();
    s->swap_file_sz = e.swap_file_sz;
    s->refcount = e.refcount;
    s->flags = e.flags;
    memcpy(s->key, e.key, SQUID_MD5_DIGEST_LENGTH);
    s->finalize();
    file_write(swaplog_fd,
               -1,
               s,
               sizeof(StoreSwapLogData),
               NULL,
               NULL,
               FreeObject);
}