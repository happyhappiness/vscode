static bool setSerialNumber(ASN1_INTEGER *ai, BIGNUM const* serial)
{
    if (!ai)
        return false;
    Ssl::BIGNUM_Pointer bn(BN_new());
    if (serial) {
        bn.reset(BN_dup(serial));
    } else {
        if (!bn)
            return false;

        if (!BN_pseudo_rand(bn.get(), 64, 0, 0))
            return false;
    }

    if (ai && !BN_to_ASN1_INTEGER(bn.get(), ai))
        return false;
    return true;
}