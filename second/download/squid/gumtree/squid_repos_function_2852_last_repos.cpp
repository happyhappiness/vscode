std::vector<StoreFileSystem*> &
StoreFileSystem::GetFileSystems()
{
    if (!_FileSystems)
        _FileSystems = new std::vector<StoreFileSystem *>;

    return *_FileSystems;
}