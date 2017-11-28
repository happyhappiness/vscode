const char *
LoadableModule::errorMsg()
{
    return lt_dlerror();
}