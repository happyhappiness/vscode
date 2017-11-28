void
E_P24(unsigned char *p21, unsigned char *c8, unsigned char *p24)
{
    smbhash(p24, c8, p21);
    smbhash(p24 + 8, c8, p21 + 7);
    smbhash(p24 + 16, c8, p21 + 14);
}