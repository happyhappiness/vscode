bool
ACL::Prototype::Registered(char const *aType)
{
    debugs(28, 7, "ACL::Prototype::Registered: invoked for type " << aType);

    for (iterator i = Registry->begin(); i != Registry->end(); ++i)
        if (!strcmp (aType, (*i)->typeString)) {
            debugs(28, 7, "ACL::Prototype::Registered:    yes");
            return true;
        }

    debugs(28, 7, "ACL::Prototype::Registered:    no");
    return false;
}