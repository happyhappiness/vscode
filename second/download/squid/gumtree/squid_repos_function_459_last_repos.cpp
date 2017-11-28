void
HttpReply::init()
{
    hdrCacheInit();
    sline.init();
    pstate = psReadyToParseStartLine;
    do_clean = true;
}