void
Adaptation::Ecap::CheckUnusedAdapterServices(const Adaptation::Services& cfgs)
{
    typedef std::list<ServiceRep::AdapterService>::const_iterator ASCI;
    for (ASCI loaded = TheServices.begin(); loaded != TheServices.end();
            ++loaded) {
        bool found = false;
        for (Services::const_iterator cfged = cfgs.begin();
                cfged != cfgs.end() && !found; ++cfged) {
            found = (*cfged)->cfg().uri == (*loaded)->uri().c_str();
        }
        if (!found)
            debugs(93, DBG_IMPORTANT, "Warning: loaded eCAP service has no matching " <<
                   "ecap_service config option: " << (*loaded)->uri());
    }
}