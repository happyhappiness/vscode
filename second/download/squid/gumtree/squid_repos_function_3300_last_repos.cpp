Adaptation::ServiceGroupPointer
Adaptation::FindGroup(const ServiceGroup::Id &id)
{
    typedef Groups::iterator GI;
    for (GI i = AllGroups().begin(); i != AllGroups().end(); ++i) {
        if ((*i)->id == id)
            return *i;
    }

    return NULL;
}