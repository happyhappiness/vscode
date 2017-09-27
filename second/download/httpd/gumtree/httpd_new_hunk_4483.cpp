                     *    because the client disconnected)
                     * 2) there is VPN or Firewall software installed with
                     *    buggy WSAAccept or WSADuplicateSocket implementation
                     * 3) the dynamic address / adapter has changed
                     * Give five chances, then fall back on AcceptFilter 'none'
                     */
                    closesocket(context->accept_socket);
                    context->accept_socket = INVALID_SOCKET;
                    ++err_count;
                    if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00337)
                                     "Child: Encountered too many AcceptEx "
