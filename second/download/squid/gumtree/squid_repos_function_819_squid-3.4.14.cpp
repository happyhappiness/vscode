bool
HttpReply::expectingBody(const HttpRequestMethod& req_method, int64_t& theSize) const
{
    bool expectBody = true;

    if (req_method == Http::METHOD_HEAD)
        expectBody = false;
    else if (sline.status() == Http::scNoContent)
        expectBody = false;
    else if (sline.status() == Http::scNotModified)
        expectBody = false;
    else if (sline.status() < Http::scOkay)
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