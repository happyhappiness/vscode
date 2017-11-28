bool
HttpRequest::expectingBody(const HttpRequestMethod &, int64_t &theSize) const
{
    bool expectBody = false;

    /*
     * Note: Checks for message validity is in clientIsContentLengthValid().
     * this just checks if a entity-body is expected based on HTTP message syntax
     */
    if (header.chunked()) {
        expectBody = true;
        theSize = -1;
    } else if (content_length >= 0) {
        expectBody = true;
        theSize = content_length;
    } else {
        expectBody = false;
        // theSize undefined
    }

    return expectBody;
}