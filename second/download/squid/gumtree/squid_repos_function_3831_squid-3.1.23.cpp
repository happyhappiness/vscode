void
Adaptation::Ecap::RegisterAdapterService(const Adaptation::Ecap::ServiceRep::AdapterService& adapterService)
{
    typedef std::list<ServiceRep::AdapterService>::iterator ASI;
    for (ASI s = TheServices.begin(); s != TheServices.end(); ++s) {
        Must(*s);
        if (adapterService->uri() == (*s)->uri()) {
            *s = adapterService;
            debugs(93, 3, "updated eCAP module service: " <<
                   adapterService->uri());
            return;
        }
    }
    TheServices.push_back(adapterService);
    debugs(93, 3, "registered eCAP module service: " << adapterService->uri());
}