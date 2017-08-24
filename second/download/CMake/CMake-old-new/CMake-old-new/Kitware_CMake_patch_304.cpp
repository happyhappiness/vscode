@@ -147,12 +147,12 @@ bool cmComputeTargetDepends::Compute()
 
 //----------------------------------------------------------------------------
 void
-cmComputeTargetDepends::GetTargetDirectDepends(cmTarget const* t,
+cmComputeTargetDepends::GetTargetDirectDepends(cmGeneratorTarget const* t,
                                                cmTargetDependSet& deps)
 {
   // Lookup the index for this target.  All targets should be known by
   // this point.
-  std::map<cmTarget const*, int>::const_iterator tii
+  std::map<cmGeneratorTarget const*, int>::const_iterator tii
                                                   = this->TargetIndex.find(t);
   assert(tii != this->TargetIndex.end());
   int i = tii->second;
@@ -161,7 +161,7 @@ cmComputeTargetDepends::GetTargetDirectDepends(cmTarget const* t,
   EdgeList const& nl = this->FinalGraph[i];
   for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
     {
-    cmTarget const* dep = this->Targets[*ni];
+    cmGeneratorTarget const* dep = this->Targets[*ni];
     cmTargetDependSet::iterator di = deps.insert(dep).first;
     di->SetType(ni->IsStrong());
     }
@@ -180,9 +180,11 @@ void cmComputeTargetDepends::CollectTargets()
         ti != targets.end(); ++ti)
       {
       cmTarget const* target = &ti->second;
+      cmGeneratorTarget* gt =
+          this->GlobalGenerator->GetGeneratorTarget(target);
       int index = static_cast<int>(this->Targets.size());
-      this->TargetIndex[target] = index;
-      this->Targets.push_back(target);
+      this->TargetIndex[gt] = index;
+      this->Targets.push_back(gt);
       }
     }
 }
@@ -204,7 +206,7 @@ void cmComputeTargetDepends::CollectDepends()
 void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
 {
   // Get the depender.
-  cmTarget const* depender = this->Targets[depender_index];
+  cmGeneratorTarget const* depender = this->Targets[depender_index];
   if (depender->GetType() == cmTarget::INTERFACE_LIBRARY)
     {
     return;
@@ -216,10 +218,9 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
   // deal with config-specific dependencies.
   {
   std::set<std::string> emitted;
-  cmGeneratorTarget* gt = this->GlobalGenerator->GetGeneratorTarget(depender);
 
   std::vector<std::string> configs;
-  depender->GetMakefile()->GetConfigurations(configs);
+  depender->Makefile->GetConfigurations(configs);
   if (configs.empty())
     {
     configs.push_back("");
@@ -228,7 +229,7 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
     it != configs.end(); ++it)
     {
     std::vector<cmSourceFile const*> objectFiles;
-    gt->GetExternalObjects(objectFiles, *it);
+    depender->GetExternalObjects(objectFiles, *it);
     for(std::vector<cmSourceFile const*>::const_iterator
         oi = objectFiles.begin(); oi != objectFiles.end(); ++oi)
       {
@@ -244,15 +245,15 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
             ->IssueMessage(cmake::FATAL_ERROR,
                             "Only executables and non-OBJECT libraries may "
                             "reference target objects.",
-                            depender->GetBacktrace());
+                            depender->Target->GetBacktrace());
           return;
           }
-        const_cast<cmTarget*>(depender)->AddUtility(objLib);
+        const_cast<cmGeneratorTarget*>(depender)->Target->AddUtility(objLib);
         }
       }
 
     cmTarget::LinkImplementation const* impl =
-      depender->GetLinkImplementation(*it);
+      depender->Target->GetLinkImplementation(*it);
 
     // A target should not depend on itself.
     emitted.insert(depender->GetName());
@@ -272,7 +273,7 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
 
   // Loop over all utility dependencies.
   {
-  std::set<cmLinkItem> const& tutils = depender->GetUtilityItems();
+  std::set<cmLinkItem> const& tutils = depender->Target->GetUtilityItems();
   std::set<std::string> emitted;
   // A target should not depend on itself.
   emitted.insert(depender->GetName());
@@ -290,13 +291,14 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
 
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
-                                                 cmTarget const* dependee,
-                                                 const std::string& config,
-                                               std::set<std::string> &emitted)
+                                             const cmGeneratorTarget* dependee,
+                                             const std::string& config,
+                                             std::set<std::string> &emitted)
 {
-  cmTarget const* depender = this->Targets[depender_index];
+  cmGeneratorTarget const* depender = this->Targets[depender_index];
   if(cmTarget::LinkInterface const* iface =
-                                dependee->GetLinkInterface(config, depender))
+                                dependee->Target->GetLinkInterface(config,
+                                                           depender->Target))
     {
     for(std::vector<cmLinkItem>::const_iterator
         lib = iface->Libraries.begin();
@@ -317,7 +319,7 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
                                              cmLinkItem const& dependee_name,
                                              std::set<std::string> &emitted)
 {
-  cmTarget const* depender = this->Targets[depender_index];
+  cmGeneratorTarget const* depender = this->Targets[depender_index];
   cmTarget const* dependee = dependee_name.Target;
   // Skip targets that will not really be linked.  This is probably a
   // name conflict between an external library and an executable
@@ -331,16 +333,17 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
 
   if(dependee)
     {
-    this->AddInterfaceDepends(depender_index, dependee, "", emitted);
+    cmGeneratorTarget* gt =
+        this->GlobalGenerator->GetGeneratorTarget(dependee);
+    this->AddInterfaceDepends(depender_index, gt, "", emitted);
     std::vector<std::string> configs;
-    depender->GetMakefile()->GetConfigurations(configs);
+    depender->Makefile->GetConfigurations(configs);
     for (std::vector<std::string>::const_iterator it = configs.begin();
       it != configs.end(); ++it)
       {
       // A target should not depend on itself.
       emitted.insert(depender->GetName());
-      this->AddInterfaceDepends(depender_index, dependee,
-                                *it, emitted);
+      this->AddInterfaceDepends(depender_index, gt, *it, emitted);
       }
     }
 }
@@ -351,7 +354,7 @@ void cmComputeTargetDepends::AddTargetDepend(
   bool linking)
 {
   // Get the depender.
-  cmTarget const* depender = this->Targets[depender_index];
+  cmGeneratorTarget const* depender = this->Targets[depender_index];
 
   // Check the target's makefile first.
   cmTarget const* dependee = dependee_name.Target;
@@ -362,7 +365,7 @@ void cmComputeTargetDepends::AddTargetDepend(
     cmake::MessageType messageType = cmake::AUTHOR_WARNING;
     bool issueMessage = false;
     std::ostringstream e;
-    switch(depender->GetPolicyStatusCMP0046())
+    switch(depender->Target->GetPolicyStatusCMP0046())
       {
       case cmPolicies::WARN:
         e << cmPolicies::GetPolicyWarning(cmPolicies::CMP0046) << "\n";
@@ -383,7 +386,7 @@ void cmComputeTargetDepends::AddTargetDepend(
         << "\" of target \"" << depender->GetName() << "\" does not exist.";
 
       cmListFileBacktrace const* backtrace =
-        depender->GetUtilityBacktrace(dependee_name);
+        depender->Target->GetUtilityBacktrace(dependee_name);
       if(backtrace)
         {
         cm->IssueMessage(messageType, e.str(), *backtrace);
@@ -408,35 +411,39 @@ void cmComputeTargetDepends::AddTargetDepend(
 
   if(dependee)
     {
-    this->AddTargetDepend(depender_index, dependee, linking);
+    cmGeneratorTarget* gt =
+        this->GlobalGenerator->GetGeneratorTarget(dependee);
+    this->AddTargetDepend(depender_index, gt, linking);
     }
 }
 
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddTargetDepend(int depender_index,
-                                             cmTarget const* dependee,
+                                             const cmGeneratorTarget* dependee,
                                              bool linking)
 {
-  if(dependee->IsImported() ||
+  if(dependee->Target->IsImported() ||
      dependee->GetType() == cmTarget::INTERFACE_LIBRARY)
     {
     // Skip IMPORTED and INTERFACE targets but follow their utility
     // dependencies.
-    std::set<cmLinkItem> const& utils = dependee->GetUtilityItems();
+    std::set<cmLinkItem> const& utils = dependee->Target->GetUtilityItems();
     for(std::set<cmLinkItem>::const_iterator i = utils.begin();
         i != utils.end(); ++i)
       {
       if(cmTarget const* transitive_dependee = i->Target)
         {
-        this->AddTargetDepend(depender_index, transitive_dependee, false);
+        cmGeneratorTarget* gt =
+            this->GlobalGenerator->GetGeneratorTarget(transitive_dependee);
+        this->AddTargetDepend(depender_index, gt, false);
         }
       }
     }
   else
     {
     // Lookup the index for this target.  All targets should be known by
     // this point.
-    std::map<cmTarget const*, int>::const_iterator tii =
+    std::map<cmGeneratorTarget const*, int>::const_iterator tii =
       this->TargetIndex.find(dependee);
     assert(tii != this->TargetIndex.end());
     int dependee_index = tii->second;
@@ -457,13 +464,13 @@ cmComputeTargetDepends::DisplayGraph(Graph const& graph,
   for(int depender_index = 0; depender_index < n; ++depender_index)
     {
     EdgeList const& nl = graph[depender_index];
-    cmTarget const* depender = this->Targets[depender_index];
+    cmGeneratorTarget const* depender = this->Targets[depender_index];
     fprintf(stderr, "target %d is [%s]\n",
             depender_index, depender->GetName().c_str());
     for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
       int dependee_index = *ni;
-      cmTarget const* dependee = this->Targets[dependee_index];
+      cmGeneratorTarget const* dependee = this->Targets[dependee_index];
       fprintf(stderr, "  depends on target %d [%s] (%s)\n", dependee_index,
               dependee->GetName().c_str(), ni->IsStrong()? "strong" : "weak");
       }
@@ -550,11 +557,11 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c,
     {
     // Get the depender.
     int i = *ci;
-    cmTarget const* depender = this->Targets[i];
+    cmGeneratorTarget const* depender = this->Targets[i];
 
     // Describe the depender.
     e << "  \"" << depender->GetName() << "\" of type "
-      << cmTarget::GetTargetTypeName(depender->GetType()) << "\n";
+      << cmTarget::GetTargetTypeName(depender->Target->GetType()) << "\n";
 
     // List its dependencies that are inside the component.
     EdgeList const& nl = this->InitialGraph[i];
@@ -563,7 +570,7 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c,
       int j = *ni;
       if(cmap[j] == c)
         {
-        cmTarget const* dependee = this->Targets[j];
+        cmGeneratorTarget const* dependee = this->Targets[j];
         e << "    depends on \"" << dependee->GetName() << "\""
           << " (" << (ni->IsStrong()? "strong" : "weak") << ")\n";
         }