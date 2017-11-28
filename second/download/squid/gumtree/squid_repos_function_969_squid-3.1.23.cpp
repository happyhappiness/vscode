int
HttpParserReqSz(HttpParser *hp)
{
    assert(hp->state == 1);
    assert(hp->req_start != -1);
    assert(hp->req_end != -1);
    return hp->req_end - hp->req_start + 1;
}