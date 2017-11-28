Vector<StoreFileSystem*> &
StoreFileSystem::GetFileSystems()
{
    if (!_FileSystems)
        _FileSystems = new Vector<StoreFileSystem *>;

    return *_FileSystems;
}