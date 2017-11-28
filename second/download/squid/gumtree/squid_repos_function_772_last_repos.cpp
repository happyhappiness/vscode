static int
find_fstype(char *type)
{
    for (size_t i = 0; i < StoreFileSystem::FileSystems().size(); ++i)
        if (strcasecmp(type, StoreFileSystem::FileSystems().at(i)->type()) == 0)
            return (int)i;

    return (-1);
}