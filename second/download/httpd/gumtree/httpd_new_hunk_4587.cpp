#define h2_util_bb_log(c, sid, level, tag, bb) \
do { \
    char buffer[4 * 1024]; \
    const char *line = "(null)"; \
    apr_size_t len, bmax = sizeof(buffer)/sizeof(buffer[0]); \
    len = h2_util_bb_print(buffer, bmax, (tag), "", (bb)); \
    ap_log_cerror(APLOG_MARK, level, 0, (c), "bb_dump(%ld): %s", \
        ((c)->master? (c)->master->id : (c)->id), (len? buffer : line)); \
} while(0)


typedef int h2_bucket_gate(apr_bucket *b);
/**
 * Transfer buckets from one brigade to another with a limit on the 
