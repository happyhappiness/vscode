bool
HttpHeader::getByIdIfPresent(Http::HdrType id, String *result) const
{
    if (id == Http::HdrType::BAD_HDR)
        return false;
    if (!has(id))
        return false;
    if (result)
        *result = getStrOrList(id);
    return true;
}