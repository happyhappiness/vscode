ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-%d): NULL -> %s %d"
                      "[orph=%d/started=%d/done=%d/eos_in=%d/eos_out=%d]", 
                      m->id, io->id, 
                      io->response? "http" : (io->rst_error? "reset" : "?"),
                      io->response? io->response->http_status : io->rst_error,
                      io->orphaned, io->worker_started, io->worker_done,
                      io->eos_in, io->eos_out);