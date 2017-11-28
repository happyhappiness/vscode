void
Adaptation::Ecap::UnregisterAdapterService(const String& serviceUri)
{
    typedef std::list<ServiceRep::AdapterService>::iterator ASI;
    for (ASI s = TheServices.begin(); s != TheServices.end(); ++s) {
        if (serviceUri == (*s)->uri().c_str()) {
            TheServices.erase(s);
            debugs(93, 3, "unregistered eCAP module service: " << serviceUri);
            return;
        }
    }
    debugs(93, 3, "failed to unregister eCAP module service: " << serviceUri);
}