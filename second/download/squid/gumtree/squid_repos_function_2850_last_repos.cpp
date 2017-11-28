void
StoreFileSystem::FsAdd(StoreFileSystem &instance)
{
    iterator i = GetFileSystems().begin();

    while (i != GetFileSystems().end()) {
        assert(strcmp((*i)->type(), instance.type()) != 0);
        ++i;
    }

    GetFileSystems().push_back (&instance);
}