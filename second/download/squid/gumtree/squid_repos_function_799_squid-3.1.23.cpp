bool
HttpReply::receivedBodyTooLarge(HttpRequest& request, int64_t receivedSize)
{
    calcMaxBodySize(request);
    debugs(58, 3, HERE << receivedSize << " >? " << bodySizeMax);
    return bodySizeMax >= 0 && receivedSize > bodySizeMax;
}