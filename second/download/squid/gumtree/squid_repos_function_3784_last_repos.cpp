static bool createSerial(Ssl::BIGNUM_Pointer &serial, Ssl::CertificateProperties const &properties)
{
    Ssl::EVP_PKEY_Pointer fakePkey;
    Security::CertPointer fakeCert;

    serial.reset(x509Pubkeydigest(properties.signWithX509));
    if (!serial.get()) {
        serial.reset(BN_new());
        BN_zero(serial.get());
    }

    if (!generateFakeSslCertificate(fakeCert, fakePkey, properties, serial))
        return false;

    // The x509Fingerprint return an SHA1 hash.
    // both SHA1 hash and maximum serial number size are 20 bytes.
    BIGNUM *r = x509Digest(fakeCert);
    if (!r)
        return false;

    serial.reset(r);
    return true;
}