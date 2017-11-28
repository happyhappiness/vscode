void
Security::PeerConnector::handleNegotiateError(const int ret)
{
    const int fd = serverConnection()->fd;
    const Security::SessionPointer session(fd_table[fd].ssl);
    unsigned long ssl_lib_error = ret;

#if USE_OPENSSL
    const int ssl_error = SSL_get_error(session.get(), ret);

    switch (ssl_error) {
    case SSL_ERROR_WANT_READ:
        noteWantRead();
        return;

    case SSL_ERROR_WANT_WRITE:
        noteWantWrite();
        return;

    case SSL_ERROR_SSL:
    case SSL_ERROR_SYSCALL:
        ssl_lib_error = ERR_get_error();
        // proceed to the general error handling code
        break;
    default:
        // no special error handling for all other errors
        ssl_lib_error = SSL_ERROR_NONE;
        break;
    }

#elif USE_GNUTLS
    const int ssl_error = ret;

    switch (ret) {
    case GNUTLS_E_WARNING_ALERT_RECEIVED: {
        auto alert = gnutls_alert_get(session.get());
        debugs(83, DBG_IMPORTANT, "TLS ALERT: " << gnutls_alert_get_name(alert));
    }
    // drop through to next case

    case GNUTLS_E_AGAIN:
    case GNUTLS_E_INTERRUPTED:
        if (gnutls_record_get_direction(session.get()) == 0)
            noteWantRead();
        else
            noteWantWrite();
        return;

    default:
        // no special error handling for all other errors
        break;
    }

#else
    // this avoids unused variable compiler warnings.
    Must(!session);
    const int ssl_error = ret;
#endif

    // Log connection details, if any
    recordNegotiationDetails();
    noteNegotiationError(ret, ssl_error, ssl_lib_error);
}