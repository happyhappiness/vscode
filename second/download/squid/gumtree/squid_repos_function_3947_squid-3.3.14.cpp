Adaptation::Ecap::ServiceRep::AdapterService
Adaptation::Ecap::FindAdapterService(const String& serviceUri)
{
    typedef std::list<ServiceRep::AdapterService>::const_iterator ASCI;
    for (ASCI s = TheServices.begin(); s != TheServices.end(); ++s) {
        Must(*s);
        if (serviceUri == (*s)->uri().c_str())
            return *s;
    }
    return ServiceRep::AdapterService();
}