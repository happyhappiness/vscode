int
HttpParserReqSz(HttpParser *hp)
{
    assert(hp->state == HTTP_PARSE_NEW);
    assert(hp->req.start != -1);
    assert(hp->req.end != -1);
    return hp->req.end - hp->req.start + 1;
}