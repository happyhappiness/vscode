uLong ZEXPORT adler32_combine64(adler1, adler2, len2)
    uLong adler1;
    uLong adler2;
    z_off64_t len2;
{
    return adler32_combine_(adler1, adler2, len2);
}