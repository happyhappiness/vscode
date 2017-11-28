void *
LoadableModule::openModule(int mode)
{
    return lt_dlopen(theName.termedBuf());
}