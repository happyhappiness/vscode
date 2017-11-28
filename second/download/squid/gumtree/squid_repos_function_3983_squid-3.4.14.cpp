Adaptation::ServicePointer
Adaptation::Ecap::Config::createService(const ServiceConfigPointer &cfg)
{
    return new Adaptation::Ecap::ServiceRep(cfg);
}