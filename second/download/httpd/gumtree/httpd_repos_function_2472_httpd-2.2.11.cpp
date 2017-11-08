static void close_worker_sockets(void)
{
    int i;
    for (i = 0; i < ap_threads_per_child; i++) {
        if (worker_sockets[i]) {
            apr_socket_close(worker_sockets[i]);
            worker_sockets[i] = NULL;
        }
    }
}