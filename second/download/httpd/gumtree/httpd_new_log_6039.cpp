ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_slave_in(%s): read, mode=%d, block=%d, readbytes=%ld", 
                  task->id, mode, block, (long)readbytes);