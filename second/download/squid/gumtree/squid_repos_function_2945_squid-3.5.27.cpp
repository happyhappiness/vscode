bool
etagIsStrongEqual(const ETag &tag1, const ETag &tag2)
{
    return !tag1.weak && !tag2.weak && etagStringsMatch(tag1, tag2);
}