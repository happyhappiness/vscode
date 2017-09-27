
/* An array of socket descriptors in use by each thread used to
 * perform a non-graceful (forced) shutdown of the server.
 */
static apr_socket_t **worker_sockets;

static void disable_listensocks(int process_slot)
{
    int i;
    for (i = 0; i < num_listensocks; i++) {
        apr_pollset_remove(event_pollset, &listener_pollfd[i]);
    }
    ap_scoreboard_image->parent[process_slot].not_accepting = 1;
}

static void enable_listensocks(int process_slot)
{
    int i;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00457)
                 "Accepting new connections again: "
                 "%u active conns, %u idle workers",
                 apr_atomic_read32(&connection_count),
                 ap_queue_info_get_idlers(worker_queue_info));
    for (i = 0; i < num_listensocks; i++)
        apr_pollset_add(event_pollset, &listener_pollfd[i]);
    /*
     * XXX: This is not yet optimal. If many workers suddenly become available,
     * XXX: the parent may kill some processes off too soon.
     */
    ap_scoreboard_image->parent[process_slot].not_accepting = 0;
}

static void close_worker_sockets(void)
{
    int i;
    for (i = 0; i < threads_per_child; i++) {
        if (worker_sockets[i]) {
            apr_socket_close(worker_sockets[i]);
