Vector<DiskIOModule*> &
DiskIOModule::GetModules()
{
    if (!_Modules)
        _Modules = new Vector<DiskIOModule *>;

    return *_Modules;
}