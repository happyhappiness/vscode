void
SMBNTencrypt(uchar * passwd, uchar * c8, uchar * p24)
{
    uchar p21[21];

    memset(p21, '\0', 21);

    E_md4hash(passwd, p21);
    E_P24(p21, c8, p24);
}