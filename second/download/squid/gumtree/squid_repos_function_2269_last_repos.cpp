String
HttpHeader::getByName(const SBuf &name) const
{
    String result;
    // ignore presence: return undefined string if an empty header is present
    (void)hasNamed(name, &result);
    return result;
}