void
Adaptation::Ecap::Host::Register()
{
    if (!TheHost) {
        TheHost.reset(new Adaptation::Ecap::Host);
        libecap::RegisterHost(TheHost);
    }
}