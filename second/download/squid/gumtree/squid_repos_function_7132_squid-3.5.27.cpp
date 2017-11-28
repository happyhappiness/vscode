StoreEntry*
Mgr::Action::createStoreEntry() const
{
    const ActionParams &params = command().params;
    const char *uri = params.httpUri.termedBuf();
    return storeCreateEntry(uri, uri, params.httpFlags, params.httpMethod);
}