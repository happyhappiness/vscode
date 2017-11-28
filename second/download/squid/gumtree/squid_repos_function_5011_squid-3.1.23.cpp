void
DiskIOModule::SetupAllModules()
{
    DiskIOModule::PokeAllModules();

    for (iterator i = GetModules().begin(); i != GetModules().end(); ++i)
        /* Call the FS to set up capabilities and initialize the FS driver */
        (*i)->init();
}