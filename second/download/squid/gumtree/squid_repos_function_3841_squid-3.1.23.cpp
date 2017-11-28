void
Adaptation::Ecap::Config::finalize()
{
    Adaptation::Config::finalize();
    Host::Register();
    CheckUnusedAdapterServices(AllServices());
}