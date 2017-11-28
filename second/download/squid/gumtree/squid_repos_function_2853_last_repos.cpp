void
StoreFileSystem::FreeAllFs()
{
    while (!GetFileSystems().empty()) {
        StoreFileSystem *fs = GetFileSystems().back();
        GetFileSystems().pop_back();
        fs->done();
    }
}