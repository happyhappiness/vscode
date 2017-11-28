static  BIGNUM *createCertSerial(unsigned char *md, unsigned int n)
{

    assert(n == 20); //for sha1 n is 20 (for md5 n is 16)

    BIGNUM *serial = NULL;
    serial = BN_bin2bn(md, n, NULL);

    // if the serial is "0" set it to '1'
    if (BN_is_zero(serial) == true)
        BN_one(serial);

    // serial size does not exceed 20 bytes
    assert(BN_num_bits(serial) <= 160);

    // According the RFC 5280, serial is an 20 bytes ASN.1 INTEGER (a signed big integer)
    // and the maximum value for X.509 certificate serial number is 2^159-1 and
    // the minimum 0. If the first bit of the serial is '1' ( eg 2^160-1),
    // will result to a negative integer.
    // To handle this, if the produced serial is greater than 2^159-1
    // truncate the last bit
    if (BN_is_bit_set(serial, 159))
        BN_clear_bit(serial, 159);

    return serial;
}