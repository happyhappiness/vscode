void Ssl::CrtdMessage::composeRequest(Ssl::CertificateProperties const &certProperties)
{
    body.clear();
    body = Ssl::CrtdMessage::param_host + "=" + certProperties.commonName;
    if (certProperties.setCommonName)
        body +=  "\n" + Ssl::CrtdMessage::param_SetCommonName + "=" + certProperties.commonName;
    if (certProperties.setValidAfter)
        body +=  "\n" + Ssl::CrtdMessage::param_SetValidAfter + "=on";
    if (certProperties.setValidBefore)
        body +=  "\n" + Ssl::CrtdMessage::param_SetValidBefore + "=on";
    if (certProperties.signAlgorithm != Ssl::algSignEnd)
        body +=  "\n" +  Ssl::CrtdMessage::param_Sign + "=" +  certSignAlgorithm(certProperties.signAlgorithm);

    std::string certsPart;
    if (!Ssl::writeCertAndPrivateKeyToMemory(certProperties.signWithX509, certProperties.signWithPkey, certsPart))
        throw std::runtime_error("Ssl::writeCertAndPrivateKeyToMemory()");
    if (certProperties.mimicCert.get()) {
        if (!Ssl::appendCertToMemory(certProperties.mimicCert, certsPart))
            throw std::runtime_error("Ssl::appendCertToMemory()");
    }
    body += "\n" + certsPart;
}