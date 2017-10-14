ap_log_error(APLOG_MARK, 
#ifdef OPENSSL_NO_TLSEXT
                         APLOG_WARNING, 
#else
                         APLOG_DEBUG, 
#endif
                         0,
                         base_server,
#ifdef OPENSSL_NO_TLSEXT
                         "Init: SSL server IP/port conflict: "
#else
                         "Init: SSL server IP/port overlap: "
#endif
                         "%s (%s:%d) vs. %s (%s:%d)",
                         ssl_util_vhostid(p, s),
                         (s->defn_name ? s->defn_name : "unknown"),
                         s->defn_line_number,
                         ssl_util_vhostid(p, ps),
                         (ps->defn_name ? ps->defn_name : "unknown"),
                         ps->defn_line_number);