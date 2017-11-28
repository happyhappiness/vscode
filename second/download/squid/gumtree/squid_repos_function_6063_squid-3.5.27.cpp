void
DiskIOModule::ModuleAdd(DiskIOModule &instance)
{
    iterator i = GetModules().begin();

    while (i != GetModules().end()) {
        assert(strcmp((*i)->type(), instance.type()) != 0);
        ++i;
    }

    GetModules().push_back (&instance);
}