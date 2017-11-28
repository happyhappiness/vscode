int64_t
HttpReply::bodySize(const HttpRequestMethod& method) const
{
    if (sline.version.major < 1)
        return -1;
    else if (method.id() == METHOD_HEAD)
        return 0;
    else if (sline.status == HTTP_OK)
        (void) 0;		/* common case, continue */
    else if (sline.status == HTTP_NO_CONTENT)
        return 0;
    else if (sline.status == HTTP_NOT_MODIFIED)
        return 0;
    else if (sline.status < HTTP_OK)
        return 0;

    return content_length;
}