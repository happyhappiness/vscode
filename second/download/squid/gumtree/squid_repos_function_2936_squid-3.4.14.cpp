bool
etagIsWeakEqual(const ETag &tag1, const ETag &tag2)
{
    return etagStringsMatch(tag1, tag2);
}