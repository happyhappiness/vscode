@@ -211,10 +211,10 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
   // dependencies in all targets, because the generated build-systems can't
   // deal with config-specific dependencies.
   {
-  std::set<cmStdString> emitted;
+  std::set<std::string> emitted;
   {
   std::vector<std::string> tlibs;
-  depender->GetDirectLinkLibraries(0, tlibs, depender);
+  depender->GetDirectLinkLibraries("", tlibs, depender);
   // A target should not depend on itself.
   emitted.insert(depender->GetName());
   for(std::vector<std::string>::const_iterator lib = tlibs.begin();
@@ -223,8 +223,8 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
     // Don't emit the same library twice for this target.
     if(emitted.insert(*lib).second)
       {
-      this->AddTargetDepend(depender_index, lib->c_str(), true);
-      this->AddInterfaceDepends(depender_index, lib->c_str(),
+      this->AddTargetDepend(depender_index, *lib, true);
+      this->AddInterfaceDepends(depender_index, *lib,
                                 true, emitted);
       }
     }
@@ -235,7 +235,7 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
     it != configs.end(); ++it)
     {
     std::vector<std::string> tlibs;
-    depender->GetDirectLinkLibraries(it->c_str(), tlibs, depender);
+    depender->GetDirectLinkLibraries(*it, tlibs, depender);
 
     // A target should not depend on itself.
     emitted.insert(depender->GetName());
@@ -245,8 +245,8 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
       // Don't emit the same library twice for this target.
       if(emitted.insert(*lib).second)
         {
-        this->AddTargetDepend(depender_index, lib->c_str(), true);
-        this->AddInterfaceDepends(depender_index, lib->c_str(),
+        this->AddTargetDepend(depender_index, *lib, true);
+        this->AddInterfaceDepends(depender_index, *lib,
                                   true, emitted);
         }
       }
@@ -255,17 +255,17 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
 
   // Loop over all utility dependencies.
   {
-  std::set<cmStdString> const& tutils = depender->GetUtilities();
-  std::set<cmStdString> emitted;
+  std::set<std::string> const& tutils = depender->GetUtilities();
+  std::set<std::string> emitted;
   // A target should not depend on itself.
   emitted.insert(depender->GetName());
-  for(std::set<cmStdString>::const_iterator util = tutils.begin();
+  for(std::set<std::string>::const_iterator util = tutils.begin();
       util != tutils.end(); ++util)
     {
     // Don't emit the same utility twice for this target.
     if(emitted.insert(*util).second)
       {
-      this->AddTargetDepend(depender_index, util->c_str(), false);
+      this->AddTargetDepend(depender_index, *util, false);
       }
     }
   }
@@ -274,8 +274,8 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
                                                  cmTarget const* dependee,
-                                                 const char *config,
-                                               std::set<cmStdString> &emitted)
+                                                 const std::string& config,
+                                               std::set<std::string> &emitted)
 {
   cmTarget const* depender = this->Targets[depender_index];
   if(cmTarget::LinkInterface const* iface =
@@ -288,8 +288,8 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
       // Don't emit the same library twice for this target.
       if(emitted.insert(*lib).second)
         {
-        this->AddTargetDepend(depender_index, lib->c_str(), true);
-        this->AddInterfaceDepends(depender_index, lib->c_str(),
+        this->AddTargetDepend(depender_index, *lib, true);
+        this->AddInterfaceDepends(depender_index, *lib,
                                   true, emitted);
         }
       }
@@ -298,9 +298,9 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
 
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
-                                             const char* dependee_name,
+                                             const std::string& dependee_name,
                                              bool linking,
-                                             std::set<cmStdString> &emitted)
+                                             std::set<std::string> &emitted)
 {
   cmTarget const* depender = this->Targets[depender_index];
   cmTarget const* dependee =
@@ -317,7 +317,7 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
 
   if(dependee)
     {
-    this->AddInterfaceDepends(depender_index, dependee, 0, emitted);
+    this->AddInterfaceDepends(depender_index, dependee, "", emitted);
     std::vector<std::string> configs;
     depender->GetMakefile()->GetConfigurations(configs);
     for (std::vector<std::string>::const_iterator it = configs.begin();
@@ -326,14 +326,14 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
       // A target should not depend on itself.
       emitted.insert(depender->GetName());
       this->AddInterfaceDepends(depender_index, dependee,
-                                it->c_str(), emitted);
+                                *it, emitted);
       }
     }
 }
 
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddTargetDepend(int depender_index,
-                                             const char* dependee_name,
+                                             const std::string& dependee_name,
                                              bool linking)
 {
   // Get the depender.
@@ -406,8 +406,8 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
   if(dependee->IsImported())
     {
     // Skip imported targets but follow their utility dependencies.
-    std::set<cmStdString> const& utils = dependee->GetUtilities();
-    for(std::set<cmStdString>::const_iterator i = utils.begin();
+    std::set<std::string> const& utils = dependee->GetUtilities();
+    for(std::set<std::string>::const_iterator i = utils.begin();
         i != utils.end(); ++i)
       {
       if(cmTarget const* transitive_dependee =
@@ -434,22 +434,23 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
 
 //----------------------------------------------------------------------------
 void
-cmComputeTargetDepends::DisplayGraph(Graph const& graph, const char* name)
+cmComputeTargetDepends::DisplayGraph(Graph const& graph,
+                                     const std::string& name)
 {
-  fprintf(stderr, "The %s target dependency graph is:\n", name);
+  fprintf(stderr, "The %s target dependency graph is:\n", name.c_str());
   int n = static_cast<int>(graph.size());
   for(int depender_index = 0; depender_index < n; ++depender_index)
     {
     EdgeList const& nl = graph[depender_index];
     cmTarget const* depender = this->Targets[depender_index];
     fprintf(stderr, "target %d is [%s]\n",
-            depender_index, depender->GetName());
+            depender_index, depender->GetName().c_str());
     for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
       int dependee_index = *ni;
       cmTarget const* dependee = this->Targets[dependee_index];
       fprintf(stderr, "  depends on target %d [%s] (%s)\n", dependee_index,
-              dependee->GetName(), ni->IsStrong()? "strong" : "weak");
+              dependee->GetName().c_str(), ni->IsStrong()? "strong" : "weak");
       }
     }
   fprintf(stderr, "\n");
@@ -471,7 +472,7 @@ ::DisplayComponents(cmComputeComponentGraph const& ccg)
       {
       int i = *ni;
       fprintf(stderr, "  contains target %d [%s]\n",
-              i, this->Targets[i]->GetName());
+              i, this->Targets[i]->GetName().c_str());
       }
     }
   fprintf(stderr, "\n");