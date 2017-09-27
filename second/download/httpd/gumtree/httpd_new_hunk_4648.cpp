    ap_scoreboard_image->parent[process_slot].not_accepting = 1;
}

static void enable_listensocks(int process_slot)
{
    int i;
    if (listener_may_exit) {
        return;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00457)
                 "Accepting new connections again: "
                 "%u active conns (%u lingering/%u clogged/%u suspended), "
                 "%u idle workers",
                 apr_atomic_read32(&connection_count),
                 apr_atomic_read32(&lingering_count),
