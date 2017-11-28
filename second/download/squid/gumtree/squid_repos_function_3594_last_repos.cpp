Adaptation::Icap::Xaction *Adaptation::Icap::ModXactLauncher::createXaction()
{
    Adaptation::Icap::ServiceRep::Pointer s =
        dynamic_cast<Adaptation::Icap::ServiceRep*>(theService.getRaw());
    Must(s != NULL);
    return new Adaptation::Icap::ModXact(virgin.header, virgin.cause, al, s);
}