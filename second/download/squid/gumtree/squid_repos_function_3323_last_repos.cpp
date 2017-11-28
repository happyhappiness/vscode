void Adaptation::History::updateNextServices(const String &services)
{
    if (theNextServices != TheNullServices)
        debugs(93,3, HERE << "old services: " << theNextServices);
    debugs(93,3, HERE << "new services: " << services);
    Must(services != TheNullServices);
    theNextServices = services;
}