 {
     debugs(28, 3, "freeing ACL " << name);
     safe_free(cfgline);
     AclMatchedName = NULL; // in case it was pointing to our name
 }
 
-ACL::Prototype::Prototype() : prototype (NULL), typeString (NULL) {}
-
-ACL::Prototype::Prototype (ACL const *aPrototype, char const *aType) : prototype (aPrototype), typeString (aType)
-{
-    registerMe ();
-}
-
-std::vector<ACL::Prototype const *> * ACL::Prototype::Registry;
-void *ACL::Prototype::Initialized;
-
-bool
-ACL::Prototype::Registered(char const *aType)
-{
-    debugs(28, 7, "ACL::Prototype::Registered: invoked for type " << aType);
-
-    for (iterator i = Registry->begin(); i != Registry->end(); ++i)
-        if (!strcmp (aType, (*i)->typeString)) {
-            debugs(28, 7, "ACL::Prototype::Registered:    yes");
-            return true;
-        }
-
-    debugs(28, 7, "ACL::Prototype::Registered:    no");
-    return false;
-}
-
-void
-ACL::Prototype::registerMe ()
-{
-    if (!Registry || (Initialized != ((char *)Registry - 5))  ) {
-        /* TODO: extract this */
-        /* Not initialised */
-        Registry = new std::vector<ACL::Prototype const *>;
-        Initialized = (char *)Registry - 5;
-    }
-
-    if (Registered (typeString))
-        fatalf ("Attempt to register %s twice", typeString);
-
-    Registry->push_back (this);
-}
-
-ACL::Prototype::~Prototype()
-{
-    // TODO: unregister me
-}
-
-ACL *
-ACL::Prototype::Factory (char const *typeToClone)
-{
-    debugs(28, 4, "ACL::Prototype::Factory: cloning an object for type '" << typeToClone << "'");
-
-    for (iterator i = Registry->begin(); i != Registry->end(); ++i)
-        if (!strcmp (typeToClone, (*i)->typeString)) {
-            ACL *A = (*i)->prototype->clone();
-            A->flags = (*i)->prototype->flags;
-            return A;
-        }
-
-    debugs(28, 4, "ACL::Prototype::Factory: cloning failed, no type '" << typeToClone << "' available");
-
-    return NULL;
-}
-
 void
 ACL::Initialize()
 {
     ACL *a = Config.aclList;
     debugs(53, 3, "ACL::Initialize");
 
