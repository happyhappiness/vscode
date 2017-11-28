static void
md5_calc(uint8_t out[16], void *in, size_t len)
{
    SquidMD5_CTX ctx;
    SquidMD5Init(&ctx);
    SquidMD5Update(&ctx, in, len);
    SquidMD5Final(out, &ctx);
}