void
Adaptation::Ecap::ConfigRep::visitEachOption(libecap::NamedValueVisitor &visitor) const
{
    // we may supply the params we know about too, but only if we set host ID
    visitor.visit(metaBypassable, Area(master.bypass ? "1" : "0", 1));

    // visit adapter-specific options (i.e., those not recognized by Squid)
    typedef Master::Extensions::const_iterator MECI;
    for (MECI i = master.extensions.begin(); i != master.extensions.end(); ++i)
        visitor.visit(Name(i->first), Area::FromTempString(i->second));
}