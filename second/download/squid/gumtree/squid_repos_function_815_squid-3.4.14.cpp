int64_t
HttpReply::bodySize(const HttpRequestMethod& method) const
{
    if (sline.version.major < 1)
        return -1;
    else if (method.id() == Http::METHOD_HEAD)
        return 0;
    else if (sline.status() == Http::scOkay)
        (void) 0;		/* common case, continue */
    else if (sline.status() == Http::scNoContent)
        return 0;
    else if (sline.status() == Http::scNotModified)
        return 0;
    else if (sline.status() < Http::scOkay)
        return 0;

    return content_length;
}