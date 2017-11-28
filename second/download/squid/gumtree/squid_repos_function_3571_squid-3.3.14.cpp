void ConnStateData::buildSslCertGenerationParams(Ssl::CertificateProperties &certProperties)
{
    certProperties.commonName =  sslCommonName.defined() ? sslCommonName.termedBuf() : sslConnectHostOrIp.termedBuf();

    // fake certificate adaptation requires bump-server-first mode
    if (!sslServerBump) {
        assert(port->signingCert.get());
        certProperties.signWithX509.resetAndLock(port->signingCert.get());
        if (port->signPkey.get())
            certProperties.signWithPkey.resetAndLock(port->signPkey.get());
        certProperties.signAlgorithm = Ssl::algSignTrusted;
        return;
    }

    // In case of an error while connecting to the secure server, use a fake
    // trusted certificate, with no mimicked fields and no adaptation
    // algorithms. There is nothing we can mimic so we want to minimize the
    // number of warnings the user will have to see to get to the error page.
    assert(sslServerBump->entry);
    if (sslServerBump->entry->isEmpty()) {
        if (X509 *mimicCert = sslServerBump->serverCert.get())
            certProperties.mimicCert.resetAndLock(mimicCert);

        ACLFilledChecklist checklist(NULL, sslServerBump->request,
                                     clientConnection != NULL ? clientConnection->rfc931 : dash_str);
        checklist.sslErrors = cbdataReference(sslServerBump->sslErrors);

        for (sslproxy_cert_adapt *ca = Config.ssl_client.cert_adapt; ca != NULL; ca = ca->next) {
            // If the algorithm already set, then ignore it.
            if ((ca->alg == Ssl::algSetCommonName && certProperties.setCommonName) ||
                    (ca->alg == Ssl::algSetValidAfter && certProperties.setValidAfter) ||
                    (ca->alg == Ssl::algSetValidBefore && certProperties.setValidBefore) )
                continue;

            if (ca->aclList && checklist.fastCheck(ca->aclList) == ACCESS_ALLOWED) {
                const char *alg = Ssl::CertAdaptAlgorithmStr[ca->alg];
                const char *param = ca->param;

                // For parameterless CN adaptation, use hostname from the
                // CONNECT request.
                if (ca->alg == Ssl::algSetCommonName) {
                    if (!param)
                        param = sslConnectHostOrIp.termedBuf();
                    certProperties.commonName = param;
                    certProperties.setCommonName = true;
                } else if (ca->alg == Ssl::algSetValidAfter)
                    certProperties.setValidAfter = true;
                else if (ca->alg == Ssl::algSetValidBefore)
                    certProperties.setValidBefore = true;

                debugs(33, 5, HERE << "Matches certificate adaptation aglorithm: " <<
                       alg << " param: " << (param ? param : "-"));
            }
        }

        certProperties.signAlgorithm = Ssl::algSignEnd;
        for (sslproxy_cert_sign *sg = Config.ssl_client.cert_sign; sg != NULL; sg = sg->next) {
            if (sg->aclList && checklist.fastCheck(sg->aclList) == ACCESS_ALLOWED) {
                certProperties.signAlgorithm = (Ssl::CertSignAlgorithm)sg->alg;
                break;
            }
        }
    } else {// if (!sslServerBump->entry->isEmpty())
        // Use trusted certificate for a Squid-generated error
        // or the user would have to add a security exception
        // just to see the error page. We will close the connection
        // so that the trust is not extended to non-Squid content.
        certProperties.signAlgorithm = Ssl::algSignTrusted;
    }

    assert(certProperties.signAlgorithm != Ssl::algSignEnd);

    if (certProperties.signAlgorithm == Ssl::algSignUntrusted) {
        assert(port->untrustedSigningCert.get());
        certProperties.signWithX509.resetAndLock(port->untrustedSigningCert.get());
        certProperties.signWithPkey.resetAndLock(port->untrustedSignPkey.get());
    } else {
        assert(port->signingCert.get());
        certProperties.signWithX509.resetAndLock(port->signingCert.get());

        if (port->signPkey.get())
            certProperties.signWithPkey.resetAndLock(port->signPkey.get());
    }
    signAlgorithm = certProperties.signAlgorithm;
}