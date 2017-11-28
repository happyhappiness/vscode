int
HttpParserRequestLen(HttpParser *hp)
{
    return hp->hdr_end - hp->req.start + 1;
}