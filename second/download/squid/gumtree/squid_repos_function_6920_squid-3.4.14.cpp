void
cred_hash2(unsigned char *out, unsigned char *in, unsigned char *key)
{
    unsigned char buf[8];
    static unsigned char key2[8];

    smbhash(buf, in, key);
    key2[0] = key[7];
    smbhash(out, buf, key2);
}