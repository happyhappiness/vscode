ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, io->connection,
                                  "h2_conn_io(%ld): read %d bytes: %s",
                                  io->connection->id, (int)bucket_length, buffer);