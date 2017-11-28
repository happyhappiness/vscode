bool
CossSwapDir::optionIOParse(char const *option, const char *value, int reconfiguring)
{
    if (strcmp(option, "IOEngine") != 0)
        return false;

    if (reconfiguring)
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