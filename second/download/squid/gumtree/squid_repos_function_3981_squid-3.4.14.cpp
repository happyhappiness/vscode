bool
Adaptation::Ecap::Config::finalize()
{
    if (!Adaptation::Config::finalize())
        return false;
    Host::Register();
    CheckUnusedAdapterServices(AllServices());
    return true;
}