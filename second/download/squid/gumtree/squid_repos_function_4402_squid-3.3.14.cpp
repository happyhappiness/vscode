static bool proccessNewRequest(Ssl::CrtdMessage & request_message, std::string const & db_path, size_t max_db_size, size_t fs_block_size)
{
    Ssl::CertificateProperties certProperties;
    std::string error;
    if (!request_message.parseRequest(certProperties, error))
        throw std::runtime_error("Error while parsing the crtd request: " + error);

    Ssl::CertificateDb db(db_path, max_db_size, fs_block_size);

    Ssl::X509_Pointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    std::string &cert_subject = certProperties.dbKey();

    db.find(cert_subject, cert, pkey);

    if (cert.get()) {
        if (!Ssl::certificateMatchesProperties(cert.get(), certProperties)) {
            // The certificate changed (renewed or other reason).
            // Generete a new one with the updated fields.
            cert.reset(NULL);
            pkey.reset(NULL);
            db.purgeCert(cert_subject);
        }
    }

    if (!cert || !pkey) {
        if (!Ssl::generateSslCertificate(cert, pkey, certProperties))
            throw std::runtime_error("Cannot create ssl certificate or private key.");

        if (!db.addCertAndPrivateKey(cert, pkey, cert_subject) && db.IsEnabledDiskStore())
            throw std::runtime_error("Cannot add certificate to db.");
    }

    std::string bufferToWrite;
    if (!Ssl::writeCertAndPrivateKeyToMemory(cert, pkey, bufferToWrite))
        throw std::runtime_error("Cannot write ssl certificate or/and private key to memory.");

    Ssl::CrtdMessage response_message;
    response_message.setCode("OK");
    response_message.setBody(bufferToWrite);

    // Use the '\1' char as end-of-message character
    std::cout << response_message.compose() << '\1' << std::flush;

    return true;
}