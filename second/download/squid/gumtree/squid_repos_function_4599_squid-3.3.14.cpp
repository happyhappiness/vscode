void
ACL::Prototype::registerMe ()
{
    if (!Registry || (Initialized != ((char *)Registry - 5))  ) {
        /* TODO: extract this */
        /* Not initialised */
        Registry = new Vector <ACL::Prototype const *>;
        Initialized = (char *)Registry - 5;
    }

    if (Registered (typeString))
        fatalf ("Attempt to register %s twice", typeString);

    Registry->push_back (this);
}