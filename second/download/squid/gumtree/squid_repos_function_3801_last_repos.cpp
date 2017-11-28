void
Ssl::ClientBio::stateChanged(const SSL *ssl, int where, int ret)
{
    Ssl::Bio::stateChanged(ssl, where, ret);
    // detect client-initiated renegotiations DoS (CVE-2011-1473)
    if (where & SSL_CB_HANDSHAKE_START) {
        const int reneg = renegotiations.count(1);

        if (abortReason)
            return; // already decided and informed the admin

        if (reneg > RenegotiationsLimit) {
            abortReason = "renegotiate requests flood";
            debugs(83, DBG_IMPORTANT, "Terminating TLS connection [from " << fd_table[fd_].ipaddr << "] due to " << abortReason << ". This connection received " <<
                   reneg << " renegotiate requests in the last " <<
                   RenegotiationsWindow << " seconds (and " <<
                   renegotiations.remembered() << " requests total).");
        }
    }
}