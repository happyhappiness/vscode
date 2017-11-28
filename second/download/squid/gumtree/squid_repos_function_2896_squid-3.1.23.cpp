bool
HttpRequest::conditional() const
{
    return flags.ims ||
           header.has(HDR_IF_MATCH) ||
           header.has(HDR_IF_NONE_MATCH);
}