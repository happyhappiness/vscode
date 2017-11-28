int
HttpParserRequestLen(HttpParser *hp)
{
    return hp->hdr_end - hp->req_start + 1;
}