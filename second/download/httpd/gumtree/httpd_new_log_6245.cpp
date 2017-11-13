ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                 ap_server_conf, APLOGNO(03096)
                                 "event_loop: unexpected state %d",
                                 cs->pub.state);