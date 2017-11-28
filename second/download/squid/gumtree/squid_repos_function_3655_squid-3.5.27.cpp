static void
clientNegotiateSSL(int fd, void *data)
{
    ConnStateData *conn = (ConnStateData *)data;
    X509 *client_cert;
    SSL *ssl = fd_table[fd].ssl;

    if (!Squid_SSL_accept(conn, clientNegotiateSSL))
        return;

    if (SSL_session_reused(ssl)) {
        debugs(83, 2, "clientNegotiateSSL: Session " << SSL_get_session(ssl) <<
               " reused on FD " << fd << " (" << fd_table[fd].ipaddr << ":" << (int)fd_table[fd].remote_port << ")");
    } else {
        if (Debug::Enabled(83, 4)) {
            /* Write out the SSL session details.. actually the call below, but
             * OpenSSL headers do strange typecasts confusing GCC.. */
            /* PEM_write_SSL_SESSION(debug_log, SSL_get_session(ssl)); */
#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x00908000L
            PEM_ASN1_write((i2d_of_void *)i2d_SSL_SESSION, PEM_STRING_SSL_SESSION, debug_log, (char *)SSL_get_session(ssl), NULL,NULL,0,NULL,NULL);

#elif (ALLOW_ALWAYS_SSL_SESSION_DETAIL == 1)

            /* When using gcc 3.3.x and OpenSSL 0.9.7x sometimes a compile error can occur here.
            * This is caused by an unpredicatble gcc behaviour on a cast of the first argument
            * of PEM_ASN1_write(). For this reason this code section is disabled. To enable it,
            * define ALLOW_ALWAYS_SSL_SESSION_DETAIL=1.
            * Because there are two possible usable cast, if you get an error here, try the other
            * commented line. */

            PEM_ASN1_write((int(*)())i2d_SSL_SESSION, PEM_STRING_SSL_SESSION, debug_log, (char *)SSL_get_session(ssl), NULL,NULL,0,NULL,NULL);
            /* PEM_ASN1_write((int(*)(...))i2d_SSL_SESSION, PEM_STRING_SSL_SESSION, debug_log, (char *)SSL_get_session(ssl), NULL,NULL,0,NULL,NULL); */

#else

            debugs(83, 4, "With " OPENSSL_VERSION_TEXT ", session details are available only defining ALLOW_ALWAYS_SSL_SESSION_DETAIL=1 in the source." );

#endif
            /* Note: This does not automatically fflush the log file.. */
        }

        debugs(83, 2, "clientNegotiateSSL: New session " <<
               SSL_get_session(ssl) << " on FD " << fd << " (" <<
               fd_table[fd].ipaddr << ":" << (int)fd_table[fd].remote_port <<
               ")");
    }

    debugs(83, 3, "clientNegotiateSSL: FD " << fd << " negotiated cipher " <<
           SSL_get_cipher(ssl));

    client_cert = SSL_get_peer_certificate(ssl);

    if (client_cert != NULL) {
        debugs(83, 3, "clientNegotiateSSL: FD " << fd <<
               " client certificate: subject: " <<
               X509_NAME_oneline(X509_get_subject_name(client_cert), 0, 0));

        debugs(83, 3, "clientNegotiateSSL: FD " << fd <<
               " client certificate: issuer: " <<
               X509_NAME_oneline(X509_get_issuer_name(client_cert), 0, 0));

        X509_free(client_cert);
    } else {
        debugs(83, 5, "clientNegotiateSSL: FD " << fd <<
               " has no certificate.");
    }

#if defined(TLSEXT_NAMETYPE_host_name)
    if (!conn->serverBump()) {
        // when in bumpClientFirst mode, get the server name from SNI
        if (const char *server = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name))
            conn->resetSslCommonName(server);
    }
#endif

    conn->readSomeData();
}