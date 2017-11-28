String
HttpHeader::getByName(const char *name) const
{
    String result;
    // ignore presence: return undefined string if an empty header is present
    (void)getByNameIfPresent(name, result);
    return result;
}