void
MemObject::setUris(char const *aStoreId, char const *aLogUri, const HttpRequestMethod &aMethod)
{
    storeId_ = aStoreId;

    // fast pointer comparison for a common storeCreateEntry(url,url,...) case
    if (!aLogUri || aLogUri == aStoreId)
        logUri_.clean(); // use storeId_ by default to minimize copying
    else
        logUri_ = aLogUri;

    method = aMethod;

#if URL_CHECKSUM_DEBUG
    chksum = url_checksum(urlXXX());
#endif
}