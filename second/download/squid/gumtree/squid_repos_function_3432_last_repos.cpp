Adaptation::Ecap::ServiceRep::AdapterService
Adaptation::Ecap::FindAdapterService(const String& serviceUri)
{
    AdapterServices::const_iterator pos = TheServices.find(serviceUri.termedBuf());
    if (pos != TheServices.end()) {
        Must(pos->second);
        return pos->second;
    }
    return ServiceRep::AdapterService();
}