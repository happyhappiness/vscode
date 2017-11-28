void
Security::NegotiationHistory::retrieveNegotiatedInfo(const Security::SessionPointer &session)
{
#if USE_OPENSSL
    if ((cipher = SSL_get_current_cipher(session.get()))) {
        // Set the negotiated version only if the cipher negotiated
        // else probably the negotiation is not completed and version
        // is not the final negotiated version
        version_ = toProtocolVersion(SSL_version(session.get()));
    }

    if (Debug::Enabled(83, 5)) {
        BIO *b = SSL_get_rbio(session.get());
        Ssl::Bio *bio = static_cast<Ssl::Bio *>(BIO_get_data(b));
        debugs(83, 5, "SSL connection info on FD " << bio->fd() <<
               " SSL version " << version_ <<
               " negotiated cipher " << cipherName());
    }
#endif
}