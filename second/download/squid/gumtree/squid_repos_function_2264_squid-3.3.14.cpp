void
httpHeaderMaskInit(HttpHeaderMask * mask, int value)
{
    memset(mask, value, sizeof(*mask));
}