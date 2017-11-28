void *LoadableModule::openModule(int mode)
{
#   if XSTD_USE_LIBLTDL
    return lt_dlopen(theName.termedBuf());
#   else
    return dlopen(theName.termedBuf(),
                  mode == lmNow ? RTLD_NOW : RTLD_LAZY);
#   endif
}