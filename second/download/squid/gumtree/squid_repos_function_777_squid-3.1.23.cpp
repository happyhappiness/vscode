void
HttpReply::init()
{
    httpBodyInit(&body);
    hdrCacheInit();
    httpStatusLineInit(&sline);
    pstate = psReadyToParseStartLine;
    do_clean = true;
}