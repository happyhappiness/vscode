DiskIOModule *
DiskIOModule::Find(char const *type)
{
    for (iterator i = GetModules().begin(); i != GetModules().end(); ++i)
        if (strcasecmp(type, (*i)->type()) == 0)
            return *i;

    return NULL;
}