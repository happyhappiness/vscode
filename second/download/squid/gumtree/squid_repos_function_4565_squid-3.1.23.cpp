void
CossStats::stat(StoreEntry *sentry)
{
    const char *tbl_fmt = "%10s %10d %10d %10d\n";
    storeAppendPrintf(sentry, "\n                   OPS     SUCCESS        FAIL\n");
    storeAppendPrintf(sentry, tbl_fmt,
                      "open", open.ops, open.success, open.fail);
    storeAppendPrintf(sentry, tbl_fmt,
                      "create", create.ops, create.success, create.fail);
    storeAppendPrintf(sentry, tbl_fmt,
                      "close", close.ops, close.success, close.fail);
    storeAppendPrintf(sentry, tbl_fmt,
                      "unlink", unlink.ops, unlink.success, unlink.fail);
    storeAppendPrintf(sentry, tbl_fmt,
                      "read", read.ops, read.success, read.fail);
    storeAppendPrintf(sentry, tbl_fmt,
                      "write", write.ops, write.success, write.fail);
    storeAppendPrintf(sentry, tbl_fmt,
                      "s_write", stripe_write.ops, stripe_write.success, stripe_write.fail);

    storeAppendPrintf(sentry, "\n");
    storeAppendPrintf(sentry, "stripes:          %d\n", stripes);
    storeAppendPrintf(sentry, "alloc.alloc:      %d\n", alloc.alloc);
    storeAppendPrintf(sentry, "alloc.realloc:    %d\n", alloc.realloc);
    storeAppendPrintf(sentry, "alloc.collisions: %d\n", alloc.collisions);
    storeAppendPrintf(sentry, "disk_overflows:   %d\n", disk_overflows);
    storeAppendPrintf(sentry, "stripe_overflows: %d\n", stripe_overflows);
    storeAppendPrintf(sentry, "open_mem_hits:    %d\n", open_mem_hits);
    storeAppendPrintf(sentry, "open_mem_misses:  %d\n", open_mem_misses);
}