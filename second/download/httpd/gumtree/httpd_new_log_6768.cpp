ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                      "h2_session(%ld): read, %s, mode=%d, readbytes=%ld", 
                      (long)f->c->id, (block == APR_BLOCK_READ)? 
                      "BLOCK_READ" : "NONBLOCK_READ", mode, (long)readbytes);