 {
     for (Auth::ConfigVector::iterator  i = cfg.begin(); i != cfg.end(); ++i)
         (*i)->dump(entry, name, (*i));
 }
 #endif /* USE_AUTH */
 
+static void
+ParseAclWithAction(acl_access **access, const allow_t &action, const char *desc, ACL *acl = nullptr)
+{
+    assert(access);
+    SBuf name;
+    if (!*access) {
+        *access = new Acl::Tree;
+        name.Printf("(%s rules)", desc);
+        (*access)->context(name.c_str(), config_input_line);
+    }
+    Acl::AndNode *rule = new Acl::AndNode;
+    name.Printf("(%s rule)", desc);
+    rule->context(name.c_str(), config_input_line);
+    acl ? rule->add(acl) : rule->lineParse();
+    (*access)->add(rule, action);
+}
+
 /* TODO: just return the object, the # is irrelevant */
 static int
 find_fstype(char *type)
 {
     for (size_t i = 0; i < StoreFileSystem::FileSystems().size(); ++i)
         if (strcasecmp(type, StoreFileSystem::FileSystems().at(i)->type()) == 0)
             return (int)i;
 
     return (-1);
 }
 
 static void
-parse_cachedir(SquidConfig::_cacheSwap * swap)
+parse_cachedir(Store::DiskConfig *swap)
 {
-    char *type_str;
-    char *path_str;
-    RefCount<SwapDir> sd;
-    int i;
-    int fs;
-
-    if ((type_str = ConfigParser::NextToken()) == NULL)
+    char *type_str = ConfigParser::NextToken();
+    if (!type_str) {
         self_destruct();
+        return;
+    }
 
-    if ((path_str = ConfigParser::NextToken()) == NULL)
+    char *path_str = ConfigParser::NextToken();
+    if (!path_str) {
         self_destruct();
+        return;
+    }
 
-    fs = find_fstype(type_str);
-
+    int fs = find_fstype(type_str);
     if (fs < 0) {
         debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: This proxy does not support the '" << type_str << "' cache type. Ignoring.");
         return;
     }
 
     /* reconfigure existing dir */
 
-    for (i = 0; i < swap->n_configured; ++i) {
+    RefCount<SwapDir> sd;
+    for (int i = 0; i < swap->n_configured; ++i) {
         assert (swap->swapDirs[i].getRaw());
 
         if ((strcasecmp(path_str, dynamic_cast<SwapDir *>(swap->swapDirs[i].getRaw())->path)) == 0) {
             /* this is specific to on-fs Stores. The right
              * way to handle this is probably to have a mapping
              * from paths to stores, and have on-fs stores
