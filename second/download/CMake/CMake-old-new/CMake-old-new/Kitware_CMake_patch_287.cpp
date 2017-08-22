@@ -172,7 +172,7 @@ satisfy dependencies.
 
 //----------------------------------------------------------------------------
 cmComputeLinkDepends
-::cmComputeLinkDepends(cmTarget const* target, const char* config,
+::cmComputeLinkDepends(cmTarget const* target, const std::string& config,
                        cmTarget const* head)
 {
   // Store context information.
@@ -184,7 +184,8 @@ ::cmComputeLinkDepends(cmTarget const* target, const char* config,
   this->CMakeInstance = this->GlobalGenerator->GetCMakeInstance();
 
   // The configuration being linked.
-  this->Config = (config && *config)? config : 0;
+  this->HasConfig = !config.empty();
+  this->Config = (this->HasConfig)? config : std::string();
   this->LinkType = this->Target->ComputeLinkType(this->Config);
 
   // Enable debug mode if requested.
@@ -254,7 +255,8 @@ cmComputeLinkDepends::Compute()
             "---------------------------------------"
             "---------------------------------------\n");
     fprintf(stderr, "Link dependency analysis for target %s, config %s\n",
-            this->Target->GetName(), this->Config?this->Config:"noconfig");
+            this->Target->GetName().c_str(),
+            this->HasConfig?this->Config.c_str():"noconfig");
     this->DisplayConstraintGraph();
     }
 
@@ -278,12 +280,12 @@ cmComputeLinkDepends::Compute()
 }
 
 //----------------------------------------------------------------------------
-std::map<cmStdString, int>::iterator
+std::map<std::string, int>::iterator
 cmComputeLinkDepends::AllocateLinkEntry(std::string const& item)
 {
-  std::map<cmStdString, int>::value_type
+  std::map<std::string, int>::value_type
     index_entry(item, static_cast<int>(this->EntryList.size()));
-  std::map<cmStdString, int>::iterator
+  std::map<std::string, int>::iterator
     lei = this->LinkEntryIndex.insert(index_entry).first;
   this->EntryList.push_back(LinkEntry());
   this->InferredDependSets.push_back(0);
@@ -296,7 +298,7 @@ int cmComputeLinkDepends::AddLinkEntry(int depender_index,
                                        std::string const& item)
 {
   // Check if the item entry has already been added.
-  std::map<cmStdString, int>::iterator lei = this->LinkEntryIndex.find(item);
+  std::map<std::string, int>::iterator lei = this->LinkEntryIndex.find(item);
   if(lei != this->LinkEntryIndex.end())
     {
     // Yes.  We do not need to follow the item's dependencies again.
@@ -310,7 +312,7 @@ int cmComputeLinkDepends::AddLinkEntry(int depender_index,
   int index = lei->second;
   LinkEntry& entry = this->EntryList[index];
   entry.Item = item;
-  entry.Target = this->FindTargetToLink(depender_index, entry.Item.c_str());
+  entry.Target = this->FindTargetToLink(depender_index, entry.Item);
   entry.IsFlag = (!entry.Target && item[0] == '-' && item[1] != 'l' &&
                   item.substr(0, 10) != "-framework");
 
@@ -326,7 +328,7 @@ int cmComputeLinkDepends::AddLinkEntry(int depender_index,
     // Look for an old-style <item>_LIB_DEPENDS variable.
     std::string var = entry.Item;
     var += "_LIB_DEPENDS";
-    if(const char* val = this->Makefile->GetDefinition(var.c_str()))
+    if(const char* val = this->Makefile->GetDefinition(var))
       {
       // The item dependencies are known.  Follow them.
       BFSEntry qe = {index, val};
@@ -422,7 +424,7 @@ ::QueueSharedDependencies(int depender_index,
 void cmComputeLinkDepends::HandleSharedDependency(SharedDepEntry const& dep)
 {
   // Check if the target already has an entry.
-  std::map<cmStdString, int>::iterator lei =
+  std::map<std::string, int>::iterator lei =
     this->LinkEntryIndex.find(dep.Item);
   if(lei == this->LinkEntryIndex.end())
     {
@@ -433,7 +435,7 @@ void cmComputeLinkDepends::HandleSharedDependency(SharedDepEntry const& dep)
     LinkEntry& entry = this->EntryList[lei->second];
     entry.Item = dep.Item;
     entry.Target = this->FindTargetToLink(dep.DependerIndex,
-                                          dep.Item.c_str());
+                                          dep.Item);
 
     // This item was added specifically because it is a dependent
     // shared library.  It may get special treatment
@@ -504,7 +506,7 @@ void cmComputeLinkDepends::AddVarLinkEntries(int depender_index,
         {
         std::string var = *di;
         var += "_LINK_TYPE";
-        if(const char* val = this->Makefile->GetDefinition(var.c_str()))
+        if(const char* val = this->Makefile->GetDefinition(var))
           {
           if(strcmp(val, "debug") == 0)
             {
@@ -620,7 +622,7 @@ cmComputeLinkDepends::AddLinkEntries(int depender_index,
 
 //----------------------------------------------------------------------------
 cmTarget const* cmComputeLinkDepends::FindTargetToLink(int depender_index,
-                                                 const char* name)
+                                                 const std::string& name)
 {
   // Look for a target in the scope of the depender.
   cmMakefile* mf = this->Makefile;
@@ -968,14 +970,14 @@ int cmComputeLinkDepends::ComputeComponentCount(NodeList const& nl)
 //----------------------------------------------------------------------------
 void cmComputeLinkDepends::DisplayFinalEntries()
 {
-  fprintf(stderr, "target [%s] links to:\n", this->Target->GetName());
+  fprintf(stderr, "target [%s] links to:\n", this->Target->GetName().c_str());
   for(std::vector<LinkEntry>::const_iterator lei =
         this->FinalLinkEntries.begin();
       lei != this->FinalLinkEntries.end(); ++lei)
     {
     if(lei->Target)
       {
-      fprintf(stderr, "  target [%s]\n", lei->Target->GetName());
+      fprintf(stderr, "  target [%s]\n", lei->Target->GetName().c_str());
       }
     else
       {
@@ -998,7 +1000,7 @@ void cmComputeLinkDepends::CheckWrongConfigItem(int depender_index,
   // directories of targets linked in another configuration as link
   // directories.
   if(cmTarget const* tgt
-                      = this->FindTargetToLink(depender_index, item.c_str()))
+                      = this->FindTargetToLink(depender_index, item))
     {
     if(!tgt->IsImported())
       {