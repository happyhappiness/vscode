const SBuf
HttpRequest::storeId()
{
    if (store_id.size() != 0) {
        debugs(73, 3, "sent back store_id: " << store_id);
        return StringToSBuf(store_id);
    }
    debugs(73, 3, "sent back effectiveRequestUrl: " << effectiveRequestUri());
    return effectiveRequestUri();
}