ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03347)
                              "h2_mplx(%ld): stream for response %d closed, "
                              "resetting io to close request processing",
                              m->id, io->id);