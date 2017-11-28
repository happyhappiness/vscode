bool
StoreMetaMD5::validLength(int len) const
{
    return len == SQUID_MD5_DIGEST_LENGTH;
}