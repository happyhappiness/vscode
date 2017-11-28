ACL *
ACL::Prototype::Factory (char const *typeToClone)
{
    debugs(28, 4, "ACL::Prototype::Factory: cloning an object for type '" << typeToClone << "'");

    for (iterator i = Registry->begin(); i != Registry->end(); ++i)
        if (!strcmp (typeToClone, (*i)->typeString)) {
            ACL *A = (*i)->prototype->clone();
            A->flags = (*i)->prototype->flags;
            return A;
        }

    debugs(28, 4, "ACL::Prototype::Factory: cloning failed, no type '" << typeToClone << "' available");

    return NULL;
}