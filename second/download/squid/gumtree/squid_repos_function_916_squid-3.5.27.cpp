void
comm_close_complete(const FdeCbParams &params)
{
#if USE_OPENSSL
    fde *F = &fd_table[params.fd];

    if (F->ssl) {
        SSL_free(F->ssl);
        F->ssl = NULL;
    }

    if (F->dynamicSslContext) {
        SSL_CTX_free(F->dynamicSslContext);
        F->dynamicSslContext = NULL;
    }
#endif
    fd_close(params.fd);        /* update fdstat */
    close(params.fd);

    ++ statCounter.syscalls.sock.closes;

    /* When one connection closes, give accept() a chance, if need be */
    Comm::AcceptLimiter::Instance().kick();
}