void
HttpReply::init()
{
    hdrCacheInit();
    httpStatusLineInit(&sline);
    pstate = psReadyToParseStartLine;
    do_clean = true;
}