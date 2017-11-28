bool
StoreEntry::hasIfNoneMatchEtag(const HttpRequest &request) const
{
    const String reqETags = request.header.getList(Http::HdrType::IF_NONE_MATCH);
    // weak comparison is allowed only for HEAD or full-body GET requests
    const bool allowWeakMatch = !request.flags.isRanged &&
                                (request.method == Http::METHOD_GET || request.method == Http::METHOD_HEAD);
    return hasOneOfEtags(reqETags, allowWeakMatch);
}