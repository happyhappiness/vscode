const libecap::Area
Adaptation::Ecap::ConfigRep::option(const libecap::Name &name) const
{
    // we may supply the params we know about, but only when names have host ID
    if (name == metaBypassable)
        return Area(master.bypass ? "1" : "0", 1);

    // TODO: We could build a by-name index, but is it worth it? Good adapters
    // should use visitEachOption() instead, to check for name typos/errors.
    typedef Master::Extensions::const_iterator MECI;
    for (MECI i = master.extensions.begin(); i != master.extensions.end(); ++i) {
        if (name == i->first)
            return Area(i->second.data(), i->second.size());
    }

    return Area();
}