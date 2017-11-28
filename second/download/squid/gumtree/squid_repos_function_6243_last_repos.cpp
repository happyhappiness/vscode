std::vector<DiskIOModule*> &
DiskIOModule::GetModules()
{
    if (!_Modules)
        _Modules = new std::vector<DiskIOModule *>;

    return *_Modules;
}