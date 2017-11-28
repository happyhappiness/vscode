void
Adaptation::Ecap::UnregisterAdapterService(const String& serviceUri)
{
    if (TheServices.erase(serviceUri.termedBuf())) {
        debugs(93, 3, "unregistered eCAP module service: " << serviceUri);
        AsyncServices.erase(serviceUri.termedBuf()); // no-op for non-async
        return;
    }
    debugs(93, 3, "failed to unregister eCAP module service: " << serviceUri);
}