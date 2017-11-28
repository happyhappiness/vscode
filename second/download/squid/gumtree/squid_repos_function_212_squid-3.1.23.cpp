void
cred_hash1(unsigned char *out, unsigned char *in, unsigned char *key)
{
    unsigned char buf[8];

    smbhash(buf, in, key);
    smbhash(out, buf, key + 9);
}