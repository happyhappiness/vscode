 *    connections off the network and calls PostQueuedCompletionStatus() to
 *    queue an io completion packet to the ThreadDispatch IOCompletionPort.
 * winnt_get_connection()
 *    Worker threads block on the ThreadDispatch IOCompletionPort awaiting 
 *    connections to service.
 */
static void winnt_accept(void *listen_socket) 
{
    apr_os_sock_info_t sockinfo;
    PCOMP_CONTEXT context;
    DWORD BytesRead;
    SOCKET nlsd;
    int lasterror;

    nlsd = (SOCKET) listen_socket;

    while (!shutdown_in_progress) {
        context = mpm_get_completion_context();
        if (!context) {
            /* Hopefully whatever is preventing us from getting a 
             * completion context is a temporary resource constraint.
             * Yield the rest of our time slice.
             */
            Sleep(0);
            continue;
        }

    again:            
        /* Create and initialize the accept socket */
        if (context->accept_socket == INVALID_SOCKET) {
            context->accept_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (context->accept_socket == INVALID_SOCKET) {
                /* Another temporary condition? */
                ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                             "winnt_accept: Failed to allocate an accept socket. "
                             "Temporary resource constraint? Try again.");
                Sleep(100);
                goto again;
            }
        }

        /* AcceptEx on the completion context. The completion context will be 
         * signaled when a connection is accepted. 
         */
