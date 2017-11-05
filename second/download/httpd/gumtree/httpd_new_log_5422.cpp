ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
                      "h2_conn_io(%ld): timeout write size reset to %ld", 
                      (long)io->c->id, (long)io->write_size);