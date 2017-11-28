static bool
etagStringsMatch(const ETag &tag1, const ETag &tag2)
{
    return !strcmp(tag1.str, tag2.str);
}