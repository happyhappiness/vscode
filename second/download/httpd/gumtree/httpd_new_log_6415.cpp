ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL, APLOGNO(02311)
                     "Fatal error initialising mod_ssl, exiting. "
                     "See %s for more information",
                     ap_server_root_relative(s->process->pool,
                                             s->error_fname));