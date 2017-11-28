bool
Fs::Ufs::UFSSwapDir::optionIOParse(char const *option, const char *value, int isaReconfig)
{
    if (strcmp(option, "IOEngine") != 0)
        return false;

    if (isaReconfig)
        /* silently ignore this */
        return true;

    if (!value)
        self_destruct();

    DiskIOModule *module = DiskIOModule::Find(value);

    if (!module)
        self_destruct();

    changeIO(module);

    return true;
}