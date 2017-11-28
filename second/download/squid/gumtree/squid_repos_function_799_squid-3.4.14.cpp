void
httpReplyInitModule(void)
{
    assert(Http::scNone == 0); // HttpReply::parse() interface assumes that
    httpHeaderMaskInit(&Denied304HeadersMask, 0);
    httpHeaderCalcMask(&Denied304HeadersMask, Denied304HeadersArr, countof(Denied304HeadersArr));
}