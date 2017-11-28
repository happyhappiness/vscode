bool
StoreEntry::hasOneOfEtags(const String &reqETags, const bool allowWeakMatch) const
{
    const ETag repETag = getReply()->header.getETag(Http::HdrType::ETAG);
    if (!repETag.str)
        return strListIsMember(&reqETags, "*", ',');

    bool matched = false;
    const char *pos = NULL;
    const char *item;
    int ilen;
    while (!matched && strListGetItem(&reqETags, ',', &item, &ilen, &pos)) {
        if (!strncmp(item, "*", ilen))
            matched = true;
        else {
            String str;
            str.append(item, ilen);
            ETag reqETag;
            if (etagParseInit(&reqETag, str.termedBuf())) {
                matched = allowWeakMatch ? etagIsWeakEqual(repETag, reqETag) :
                          etagIsStrongEqual(repETag, reqETag);
            }
        }
    }
    return matched;
}