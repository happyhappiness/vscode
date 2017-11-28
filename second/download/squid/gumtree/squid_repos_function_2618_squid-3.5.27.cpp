const char *LoadableModule::errorMsg()
{
#   if XSTD_USE_LIBLTDL
    return lt_dlerror();
#   else
    return dlerror();
#   endif
}