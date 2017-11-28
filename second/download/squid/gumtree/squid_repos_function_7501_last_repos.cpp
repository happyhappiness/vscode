static bool processNewRequest(Ssl::CrtdMessage & request_message, std::string const & db_path, size_t max_db_size, size_t fs_block_size)
{
    Ssl::CertificateProperties certProperties;
    std::string error;
    if (!request_message.parseRequest(certProperties, error))
        throw std::runtime_error("Error while parsing the crtd request: " + error);

    Ssl::CertificateDb db(db_path, max_db_size, fs_block_size);

    Security::CertPointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    std::string &cert_subject = certProperties.dbKey();

    bool dbFailed = false;
    try {
        db.find(cert_subject, cert, pkey);
    } catch (std::runtime_error &err) {
        dbFailed = true;
        error = err.what();
    }

    if (cert) {
        if (!Ssl::certificateMatchesProperties(cert.get(), certProperties)) {
            // The certificate changed (renewed or other reason).
            // Generete a new one with the updated fields.
            cert.reset();
            pkey.reset();
            db.purgeCert(cert_subject);
        }
    }

    if (!cert || !pkey) {
        if (!Ssl::generateSslCertificate(cert, pkey, certProperties))
            throw std::runtime_error("Cannot create ssl certificate or private key.");

        if (!dbFailed && db.IsEnabledDiskStore()) {
            try {
                if (!db.addCertAndPrivateKey(cert, pkey, cert_subject)) {
                    dbFailed = true;
                    error = "Cannot add certificate to db.";
                }
            } catch (const std::runtime_error &err) {
                dbFailed = true;
                error = err.what();
            }
        }
    }

    if (dbFailed)
        std::cerr << "security_file_certgen helper database '" << db_path  << "' failed: " << error << std::endl;

    std::string bufferToWrite;
    if (!Ssl::writeCertAndPrivateKeyToMemory(cert, pkey, bufferToWrite))
        throw std::runtime_error("Cannot write ssl certificate or/and private key to memory.");

    Ssl::CrtdMessage response_message(Ssl::CrtdMessage::REPLY);
    response_message.setCode("OK");
    response_message.setBody(bufferToWrite);

    // Use the '\1' char as end-of-message character
    std::cout << response_message.compose() << '\1' << std::flush;

    return true;
}