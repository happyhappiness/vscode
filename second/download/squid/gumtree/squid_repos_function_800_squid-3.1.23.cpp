bool
HttpReply::expectedBodyTooLarge(HttpRequest& request)
{
    calcMaxBodySize(request);
    debugs(58, 7, HERE << "bodySizeMax=" << bodySizeMax);

    if (bodySizeMax < 0) // no body size limit
        return false;

    int64_t expectedSize = -1;
    if (!expectingBody(request.method, expectedSize))
        return false;

    debugs(58, 6, HERE << expectedSize << " >? " << bodySizeMax);

    if (expectedSize < 0) // expecting body of an unknown length
        return false;

    return expectedSize > bodySizeMax;
}