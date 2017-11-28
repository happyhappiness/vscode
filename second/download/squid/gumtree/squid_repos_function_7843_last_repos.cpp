void
E_md4hash(uchar * passwd, uchar * p16)
{
    int len;
    int16_t wpwd[129];

    /* Password cannot be longer than 128 characters */
    len = strlen((char *) passwd);
    if (len > 128)
        len = 128;
    /* Password must be converted to NT unicode */
    _my_mbstowcs(wpwd, passwd, len);
    wpwd[len] = 0;      /* Ensure string is null terminated */
    /* Calculate length in bytes */
    len = _my_wcslen(wpwd) * sizeof(int16_t);

    mdfour(p16, (unsigned char *) wpwd, len);
}