bool
HttpRequest::conditional() const
{
    return flags.ims ||
           header.has(Http::HdrType::IF_MATCH) ||
           header.has(Http::HdrType::IF_NONE_MATCH);
}