void
AnyP::PortCfg::configureSslServerContext()
{
    if (!secure.certs.empty()) {
        Security::KeyData &keys = secure.certs.front();
        Ssl::readCertChainAndPrivateKeyFromFiles(signingCert, signPkey, certsToChain, keys.certFile.c_str(), keys.privateKeyFile.c_str());
    }

    if (!signingCert) {
        char buf[128];
        fatalf("No valid signing SSL certificate configured for %s_port %s", AnyP::ProtocolType_str[transport.protocol],  s.toUrl(buf, sizeof(buf)));
    }

    if (!signPkey)
        debugs(3, DBG_IMPORTANT, "No SSL private key configured for  " << AnyP::ProtocolType_str[transport.protocol] << "_port " << s);

    Ssl::generateUntrustedCert(untrustedSigningCert, untrustedSignPkey,
                               signingCert, signPkey);

    if (!untrustedSigningCert) {
        char buf[128];
        fatalf("Unable to generate signing SSL certificate for untrusted sites for %s_port %s", AnyP::ProtocolType_str[transport.protocol], s.toUrl(buf, sizeof(buf)));
    }

    if (clientca) {
        clientCA.reset(SSL_load_client_CA_file(clientca));
        if (clientCA.get() == NULL) {
            fatalf("Unable to read client CAs! from %s", clientca);
        }
    }

    if (!secure.createStaticServerContext(*this)) {
        char buf[128];
        fatalf("%s_port %s initialization error", AnyP::ProtocolType_str[transport.protocol], s.toUrl(buf, sizeof(buf)));
    }
}