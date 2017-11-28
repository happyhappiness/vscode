void
HttpParser::reset(const char *aBuf, int len)
{
    clear(); // empty the state.
    state = HTTP_PARSE_NEW;
    buf = aBuf;
    bufsiz = len;
    debugs(74, 5, HERE << "Request buffer is " << buf);
}