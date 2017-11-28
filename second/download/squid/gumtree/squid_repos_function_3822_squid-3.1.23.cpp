void
Adaptation::Ecap::ServiceRep::finalize()
{
    Adaptation::Service::finalize();
    theService = FindAdapterService(cfg().uri);
    if (theService) {
        debugs(93,DBG_IMPORTANT, "Starting eCAP service: " << theService->uri());
        theService->start();
    } else {
        debugs(93,DBG_IMPORTANT, "WARNING: configured ecap_service was not loaded: " << cfg().uri);
    }
}