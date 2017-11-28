Adaptation::ServicePointer
Adaptation::Icap::Config::createService(const Adaptation::ServiceConfig &cfg)
{
    return new Adaptation::Icap::ServiceRep(cfg);
}