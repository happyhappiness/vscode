bool LoadableModule::closeModule()
{
#   if XSTD_USE_LIBLTDL
    // we cast to avoid including ltdl.h in LoadableModule.h
    return lt_dlclose(static_cast<lt_dlhandle>(theHandle)) == 0;
#   else
    return dlclose(theHandle) == 0;
#   endif
}