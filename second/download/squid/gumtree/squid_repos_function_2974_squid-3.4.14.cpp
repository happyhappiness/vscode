const char *
HttpRequest::storeId()
{
    if (store_id.size() != 0) {
        debugs(73, 3, "sent back store_id:" << store_id);

        return store_id.termedBuf();
    }
    debugs(73, 3, "sent back canonicalUrl:" << urlCanonical(this) );

    return urlCanonical(this);
}