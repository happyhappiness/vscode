ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, beam->red_pool, 
                              APLOGNO(03384) "h2_beam(%d-%s): emitted bucket not "
                              "in hold, n=%d", beam->id, beam->tag, 
                              (int)proxy->n);