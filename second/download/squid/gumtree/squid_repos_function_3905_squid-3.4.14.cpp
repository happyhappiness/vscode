void
Adaptation::Config::ParseServiceGroup(ServiceGroupPointer g)
{
    assert(g != NULL);
    g->parse();
    AllGroups().push_back(g);
}