ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, io->connection,
                      "h2_conn_io(%ld): init, buffering=%d, warmup_size=%ld, cd_secs=%f",
                      io->connection->id, io->buffer_output, (long)io->warmup_size,
                      ((float)io->cooldown_usecs/APR_USEC_PER_SEC));