bool
StoreEntry::hasIfMatchEtag(const HttpRequest &request) const
{
    const String reqETags = request.header.getList(Http::HdrType::IF_MATCH);
    return hasOneOfEtags(reqETags, false);
}