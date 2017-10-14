ap_log_error(APLOG_MARK, level, 0, base_server,
                         "Init: SSL server IP/port %s: "
                         "%s (%s:%d) vs. %s (%s:%d)",
                         problem, ssl_util_vhostid(p, s),
                         (s->defn_name ? s->defn_name : "unknown"),
                         s->defn_line_number,
                         ssl_util_vhostid(p, ps),
                         (ps->defn_name ? ps->defn_name : "unknown"),
                         ps->defn_line_number);