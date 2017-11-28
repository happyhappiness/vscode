Adaptation::ServicePointer
Adaptation::Ecap::Config::createService(const Adaptation::ServiceConfig &cfg)
{
    Adaptation::ServicePointer s = new Adaptation::Ecap::ServiceRep(cfg);
    return s.getRaw();
}