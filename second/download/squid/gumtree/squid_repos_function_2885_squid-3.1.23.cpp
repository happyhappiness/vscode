bool
HttpRequest::multipartRangeRequest() const
{
    return (range && range->specs.count > 1);
}