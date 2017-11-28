bool Ssl::CrtdMessage::parseRequest(Ssl::CertificateProperties &certProperties, std::string &error)
{
    Ssl::CrtdMessage::BodyParams map;
    std::string certs_part;
    parseBody(map, certs_part);
    Ssl::CrtdMessage::BodyParams::iterator i = map.find(Ssl::CrtdMessage::param_host);
    if (i == map.end()) {
        error = "Cannot find \"host\" parameter in request message";
        return false;
    }
    certProperties.commonName = i->second;

    i = map.find(Ssl::CrtdMessage::param_SetValidAfter);
    if (i != map.end() && strcasecmp(i->second.c_str(), "on") == 0)
        certProperties.setValidAfter = true;

    i = map.find(Ssl::CrtdMessage::param_SetValidBefore);
    if (i != map.end() && strcasecmp(i->second.c_str(), "on") == 0)
        certProperties.setValidBefore = true;

    i = map.find(Ssl::CrtdMessage::param_SetCommonName);
    if (i != map.end()) {
        // use this as Common Name  instead of the hostname
        // defined with host or Common Name from mimic cert
        certProperties.commonName = i->second;
        certProperties.setCommonName = true;
    }

    i = map.find(Ssl::CrtdMessage::param_Sign);
    if (i != map.end()) {
        if ((certProperties.signAlgorithm = Ssl::certSignAlgorithmId(i->second.c_str())) == Ssl::algSignEnd) {
            error = "Wrong signing algoritm: ";
            error += i->second;
            return false;
        }
    } else
        certProperties.signAlgorithm = Ssl::algSignTrusted;

    i = map.find(Ssl::CrtdMessage::param_SignHash);
    const char *signHashName = i != map.end() ? i->second.c_str() : SQUID_SSL_SIGN_HASH_IF_NONE;
    if (!(certProperties.signHash = EVP_get_digestbyname(signHashName))) {
        error = "Wrong signing hash: ";
        error += signHashName;
        return false;
    }

    if (!Ssl::readCertAndPrivateKeyFromMemory(certProperties.signWithX509, certProperties.signWithPkey, certs_part.c_str())) {
        error = "Broken signing certificate!";
        return false;
    }

    static const std::string CERT_BEGIN_STR("-----BEGIN CERTIFICATE");
    size_t pos;
    if ((pos = certs_part.find(CERT_BEGIN_STR)) != std::string::npos) {
        pos += CERT_BEGIN_STR.length();
        if ((pos= certs_part.find(CERT_BEGIN_STR, pos)) != std::string::npos)
            Ssl::readCertFromMemory(certProperties.mimicCert, certs_part.c_str() + pos);
    }
    return true;
}