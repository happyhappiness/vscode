bool
StoreEntry::hasIfMatchEtag(const HttpRequest &request) const
{
    const String reqETags = request.header.getList(HDR_IF_MATCH);
    return hasOneOfEtags(reqETags, false);
}