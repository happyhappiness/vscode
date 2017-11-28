    // visit adapter-specific options (i.e., those not recognized by Squid)
    typedef Master::Extensions::const_iterator MECI;
    for (MECI i = master.extensions.begin(); i != master.extensions.end(); ++i)
        visitor.visit(Name(i->first), Area::FromTempString(i->second));
}

Adaptation::Ecap::ServiceRep::ServiceRep(const ServiceConfigPointer &cfg):
        /*AsyncJob("Adaptation::Ecap::ServiceRep"),*/ Adaptation::Service(cfg),
        isDetached(false)
{
}

Adaptation::Ecap::ServiceRep::~ServiceRep()
{
}
