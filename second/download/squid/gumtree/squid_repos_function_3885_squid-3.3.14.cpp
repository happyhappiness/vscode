void
Adaptation::Config::FreeServiceGroups()
{
    while (!AllGroups().empty()) {
        // groups are refcounted so we do not explicitly delete them
        AllGroups().pop_back();
    }
}