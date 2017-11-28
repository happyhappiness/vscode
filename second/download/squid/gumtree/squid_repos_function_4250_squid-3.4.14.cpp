Adaptation::ServicePointer
Adaptation::Icap::Config::createService(const ServiceConfigPointer &cfg)
{
    return new Adaptation::Icap::ServiceRep(cfg);
}