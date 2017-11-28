bool
LoadableModule::closeModule()
{
    // we cast to avoid including ltdl.h in LoadableModule.h
    return lt_dlclose(static_cast<lt_dlhandle>(theHandle)) == 0;
}