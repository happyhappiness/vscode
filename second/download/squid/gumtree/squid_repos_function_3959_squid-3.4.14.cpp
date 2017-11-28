void
Adaptation::Ecap::ServiceRep::tryConfigureAndStart()
{
    debugs(93,2, HERE << "configuring eCAP service: " << theService->uri());
    const ConfigRep cfgRep(dynamic_cast<const ServiceConfig&>(cfg()));
    theService->configure(cfgRep);

    debugs(93,DBG_IMPORTANT, "Starting eCAP service: " << theService->uri());
    theService->start();
}