bool
HttpRequest::multipartRangeRequest() const
{
    return (range && range->specs.size() > 1);
}