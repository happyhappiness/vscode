
/* An array of socket descriptors in use by each thread used to
 * perform a non-graceful (forced) shutdown of the server.
 */
static apr_socket_t **worker_sockets;

static void close_worker_sockets(void)
{
    int i;
    for (i = 0; i < threads_per_child; i++) {
        if (worker_sockets[i]) {
            apr_socket_close(worker_sockets[i]);
