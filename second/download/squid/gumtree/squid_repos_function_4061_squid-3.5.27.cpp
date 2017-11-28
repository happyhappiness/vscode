const libecap::Area
Adaptation::Ecap::XactionRep::option(const libecap::Name &name) const
{
    if (name == libecap::metaClientIp)
        return clientIpValue();
    if (name == libecap::metaUserName)
        return usernameValue();
    if (Adaptation::Config::masterx_shared_name && name == Adaptation::Config::masterx_shared_name)
        return masterxSharedValue(name);

    // TODO: metaServerIp, metaAuthenticatedUser, and metaAuthenticatedGroups

    // If the name is unknown, metaValue returns an emtpy area
    return metaValue(name);
}