void
StoreFileSystem::SetupAllFs()
{
    for (iterator i = GetFileSystems().begin(); i != GetFileSystems().end(); ++i)
        /* Call the FS to set up capabilities and initialize the FS driver */
        (*i)->setup();
}