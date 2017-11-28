void
Adaptation::Ecap::RegisterAdapterService(const Adaptation::Ecap::ServiceRep::AdapterService& adapterService)
{
    TheServices[adapterService->uri()] = adapterService; // may update old one
    debugs(93, 3, "stored eCAP module service: " << adapterService->uri());
    // We do not update AsyncServices here in case they are not configured.
}