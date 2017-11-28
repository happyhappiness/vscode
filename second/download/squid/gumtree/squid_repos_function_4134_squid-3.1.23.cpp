BIGNUM * Ssl::CertificateDb::getCurrentSerialNumber()
{
    FileLocker serial_locker(serial_full);
    // load serial number from file.
    Ssl::BIO_Pointer file(BIO_new(BIO_s_file()));
    if (!file)
        return NULL;

    if (BIO_rw_filename(file.get(), const_cast<char *>(serial_full.c_str())) <= 0)
        return NULL;

    Ssl::ASN1_INT_Pointer serial_ai(ASN1_INTEGER_new());
    if (!serial_ai)
        return NULL;

    char buffer[1024];
    if (!a2i_ASN1_INTEGER(file.get(), serial_ai.get(), buffer, sizeof(buffer)))
        return NULL;

    Ssl::BIGNUM_Pointer serial(ASN1_INTEGER_to_BN(serial_ai.get(), NULL));

    if (!serial)
        return NULL;

    // increase serial number.
    Ssl::BIGNUM_Pointer increased_serial(BN_dup(serial.get()));
    if (!increased_serial)
        return NULL;

    BN_add_word(increased_serial.get(), 1);

    // save increased serial number.
    if (BIO_seek(file.get(), 0))
        return NULL;

    Ssl::ASN1_INT_Pointer increased_serial_ai(BN_to_ASN1_INTEGER(increased_serial.get(), NULL));
    if (!increased_serial_ai)
        return NULL;

    i2a_ASN1_INTEGER(file.get(), increased_serial_ai.get());
    BIO_puts(file.get(),"\n");

    return serial.release();
}