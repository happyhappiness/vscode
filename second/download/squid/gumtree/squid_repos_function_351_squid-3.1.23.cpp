void
SMBencrypt(uchar * passwd, uchar * c8, uchar * p24)
{
    uchar p14[15], p21[21];

    memset(p21, '\0', 21);
    memset(p14, '\0', 14);
    StrnCpy((char *) p14, (char *) passwd, 14);

    strupper((char *) p14);
    E_P16(p14, p21);
    E_P24(p21, c8, p24);
}