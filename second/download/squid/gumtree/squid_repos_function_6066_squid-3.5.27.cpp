void
DiskIOModule::FreeAllModules()
{
    while (!GetModules().empty()) {
        DiskIOModule *fs = GetModules().back();
        GetModules().pop_back();
        fs->gracefulShutdown();
    }
}