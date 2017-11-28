static bool proccessNewRequest(Ssl::CrtdMessage const & request_message, std::string const & db_path, size_t max_db_size, size_t fs_block_size)
{
    Ssl::CrtdMessage::BodyParams map;
    std::string body_part;
    request_message.parseBody(map, body_part);

    Ssl::CrtdMessage::BodyParams::iterator i = map.find(Ssl::CrtdMessage::param_host);
    if (i == map.end())
        throw std::runtime_error("Cannot find \"" + Ssl::CrtdMessage::param_host + "\" parameter in request message.");
    std::string host = i->second;

    Ssl::CertificateDb db(db_path, max_db_size, fs_block_size);

    Ssl::X509_Pointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    db.find("/CN=" + host, cert, pkey);

    if (!cert || !pkey) {
        Ssl::X509_Pointer certToSign;
        Ssl::EVP_PKEY_Pointer pkeyToSign;
        Ssl::readCertAndPrivateKeyFromMemory(certToSign, pkeyToSign, body_part.c_str());

        Ssl::BIGNUM_Pointer serial(db.getCurrentSerialNumber());

        if (!Ssl::generateSslCertificateAndPrivateKey(host.c_str(), certToSign, pkeyToSign, cert, pkey, serial.get()))
            throw std::runtime_error("Cannot create ssl certificate or private key.");
        if (!db.addCertAndPrivateKey(cert, pkey) && db.IsEnabledDiskStore())
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