void
DiskIOModule::FreeAllModules()
{
    while (GetModules().size()) {
        DiskIOModule *fs = GetModules().back();
        GetModules().pop_back();
        fs->shutdown();
    }
}