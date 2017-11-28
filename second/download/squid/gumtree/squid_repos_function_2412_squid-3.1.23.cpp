void
FwdState::negotiateSSL(int fd)
{
    FwdServer *fs = servers;
    SSL *ssl = fd_table[fd].ssl;
    int ret;

    if ((ret = SSL_connect(ssl)) <= 0) {
        int ssl_error = SSL_get_error(ssl, ret);

        switch (ssl_error) {

        case SSL_ERROR_WANT_READ:
            commSetSelect(fd, COMM_SELECT_READ, fwdNegotiateSSLWrapper, this, 0);
            return;

        case SSL_ERROR_WANT_WRITE:
            commSetSelect(fd, COMM_SELECT_WRITE, fwdNegotiateSSLWrapper, this, 0);
            return;

        default:
            debugs(81, 1, "fwdNegotiateSSL: Error negotiating SSL connection on FD " << fd <<
                   ": " << ERR_error_string(ERR_get_error(), NULL) << " (" << ssl_error <<
                   "/" << ret << "/" << errno << ")");
            ErrorState *const anErr = makeConnectingError(ERR_SECURE_CONNECT_FAIL);
#ifdef EPROTO

            anErr->xerrno = EPROTO;
#else

            anErr->xerrno = EACCES;
#endif

            Ssl::ErrorDetail *errFromFailure = (Ssl::ErrorDetail *)SSL_get_ex_data(ssl, ssl_ex_index_ssl_error_detail);
            if (errFromFailure != NULL) {
                // The errFromFailure is attached to the ssl object
                // and will be released when ssl object destroyed.
                // Copy errFromFailure to a new Ssl::ErrorDetail object
                anErr->detail = new Ssl::ErrorDetail(*errFromFailure);
            }

            fail(anErr);

            if (fs->_peer) {
                peerConnectFailed(fs->_peer);
                fs->_peer->stats.conn_open--;
            }

            comm_close(fd);
            return;
        }
    }

    if (fs->_peer && !SSL_session_reused(ssl)) {
        if (fs->_peer->sslSession)
            SSL_SESSION_free(fs->_peer->sslSession);

        fs->_peer->sslSession = SSL_get1_session(ssl);
    }

    dispatch();
}