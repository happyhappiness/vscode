void
StoreFileSystem::FreeAllFs()
{
    while (GetFileSystems().size()) {
        StoreFileSystem *fs = GetFileSystems().back();
        GetFileSystems().pop_back();
        fs->done();
    }
}