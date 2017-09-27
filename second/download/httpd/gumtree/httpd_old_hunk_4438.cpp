#define h2_util_bb_log(c, sid, level, tag, bb) \
do { \
    char buffer[4 * 1024]; \
    const char *line = "(null)"; \
    apr_size_t len, bmax = sizeof(buffer)/sizeof(buffer[0]); \
    len = h2_util_bb_print(buffer, bmax, (tag), "", (bb)); \
    ap_log_cerror(APLOG_MARK, level, 0, (c), "bb_dump(%ld-%d): %s", \
        (c)->id, (int)(sid), (len? buffer : line)); \
} while(0)


/**
 * Transfer buckets from one brigade to another with a limit on the 
 * maximum amount of bytes transfered. Does no setaside magic, lifetime
 * of brigades must fit. 
 * @param to   brigade to transfer buckets to
 * @param from brigades to remove buckets from
 * @param plen maximum bytes to transfer, actual bytes transferred
 * @param peos if an EOS bucket was transferred
 */
apr_status_t h2_append_brigade(apr_bucket_brigade *to,
                               apr_bucket_brigade *from, 
                               apr_off_t *plen,
                               int *peos);

/**
 * Get an approximnation of the memory footprint of the given
 * brigade. This varies from apr_brigade_length as
 * - no buckets are ever read
 * - only buckets known to allocate memory (HEAP+POOL) are counted
