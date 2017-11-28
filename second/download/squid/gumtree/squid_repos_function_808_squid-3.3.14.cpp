bool
HttpReply::expectingBody(const HttpRequestMethod& req_method, int64_t& theSize) const
{
    bool expectBody = true;

    if (req_method == METHOD_HEAD)
        expectBody = false;
    else if (sline.status == HTTP_NO_CONTENT)
        expectBody = false;
    else if (sline.status == HTTP_NOT_MODIFIED)
        expectBody = false;
    else if (sline.status < HTTP_OK)
        expectBody = false;
    else
        expectBody = true;

    if (expectBody) {
        if (header.chunked())
            theSize = -1;
        else if (content_length >= 0)
            theSize = content_length;
        else
            theSize = -1;
    }

    return expectBody;
}