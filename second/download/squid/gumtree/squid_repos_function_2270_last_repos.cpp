String
HttpHeader::getById(Http::HdrType id) const
{
    String result;
    (void)getByIdIfPresent(id, &result);
    return result;
}