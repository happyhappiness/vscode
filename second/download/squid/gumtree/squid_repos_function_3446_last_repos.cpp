void
Adaptation::Ecap::Host::Register()
{
    if (!TheHost && SupportedVersion(libecap::VersionString(),
                                     "Squid executable dynamically linked")) {
        TheHost.reset(new Adaptation::Ecap::Host);
        libecap::RegisterHost(TheHost);
    }
}