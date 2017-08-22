@@ -143,20 +143,21 @@ bool cmComputeTargetDepends::Compute()
 
 //----------------------------------------------------------------------------
 void
-cmComputeTargetDepends::GetTargetDirectDepends(cmTarget* t,
+cmComputeTargetDepends::GetTargetDirectDepends(cmTarget const* t,
                                                cmTargetDependSet& deps)
 {
   // Lookup the index for this target.  All targets should be known by
   // this point.
-  std::map<cmTarget*, int>::const_iterator tii = this->TargetIndex.find(t);
+  std::map<cmTarget const*, int>::const_iterator tii
+                                                  = this->TargetIndex.find(t);
   assert(tii != this->TargetIndex.end());
   int i = tii->second;
 
   // Get its final dependencies.
   EdgeList const& nl = this->FinalGraph[i];
   for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
     {
-    cmTarget* dep = this->Targets[*ni];
+    cmTarget const* dep = this->Targets[*ni];
     cmTargetDependSet::iterator di = deps.insert(dep).first;
     di->SetType(ni->IsStrong());
     }
@@ -170,10 +171,11 @@ void cmComputeTargetDepends::CollectTargets()
     this->GlobalGenerator->GetLocalGenerators();
   for(unsigned int i = 0; i < lgens.size(); ++i)
     {
-    cmTargets& targets = lgens[i]->GetMakefile()->GetTargets();
-    for(cmTargets::iterator ti = targets.begin(); ti != targets.end(); ++ti)
+    const cmTargets& targets = lgens[i]->GetMakefile()->GetTargets();
+    for(cmTargets::const_iterator ti = targets.begin();
+        ti != targets.end(); ++ti)
       {
-      cmTarget* target = &ti->second;
+      cmTarget const* target = &ti->second;
       int index = static_cast<int>(this->Targets.size());
       this->TargetIndex[target] = index;
       this->Targets.push_back(target);
@@ -198,7 +200,7 @@ void cmComputeTargetDepends::CollectDepends()
 void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
 {
   // Get the depender.
-  cmTarget* depender = this->Targets[depender_index];
+  cmTarget const* depender = this->Targets[depender_index];
   if (depender->GetType() == cmTarget::INTERFACE_LIBRARY)
     {
     return;
@@ -271,11 +273,11 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
 
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
-                                                 cmTarget* dependee,
+                                                 cmTarget const* dependee,
                                                  const char *config,
                                                std::set<cmStdString> &emitted)
 {
-  cmTarget* depender = this->Targets[depender_index];
+  cmTarget const* depender = this->Targets[depender_index];
   if(cmTarget::LinkInterface const* iface =
                                 dependee->GetLinkInterface(config, depender))
     {
@@ -300,8 +302,8 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
                                              bool linking,
                                              std::set<cmStdString> &emitted)
 {
-  cmTarget* depender = this->Targets[depender_index];
-  cmTarget* dependee =
+  cmTarget const* depender = this->Targets[depender_index];
+  cmTarget const* dependee =
     depender->GetMakefile()->FindTargetToUse(dependee_name);
   // Skip targets that will not really be linked.  This is probably a
   // name conflict between an external library and an executable
@@ -335,10 +337,10 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
                                              bool linking)
 {
   // Get the depender.
-  cmTarget* depender = this->Targets[depender_index];
+  cmTarget const* depender = this->Targets[depender_index];
 
   // Check the target's makefile first.
-  cmTarget* dependee =
+  cmTarget const* dependee =
     depender->GetMakefile()->FindTargetToUse(dependee_name);
 
   // Skip targets that will not really be linked.  This is probably a
@@ -359,7 +361,7 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
 
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddTargetDepend(int depender_index,
-                                             cmTarget* dependee,
+                                             cmTarget const* dependee,
                                              bool linking)
 {
   if(dependee->IsImported())
@@ -369,7 +371,7 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
     for(std::set<cmStdString>::const_iterator i = utils.begin();
         i != utils.end(); ++i)
       {
-      if(cmTarget* transitive_dependee =
+      if(cmTarget const* transitive_dependee =
          dependee->GetMakefile()->FindTargetToUse(i->c_str()))
         {
         this->AddTargetDepend(depender_index, transitive_dependee, false);
@@ -380,7 +382,7 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
     {
     // Lookup the index for this target.  All targets should be known by
     // this point.
-    std::map<cmTarget*, int>::const_iterator tii =
+    std::map<cmTarget const*, int>::const_iterator tii =
       this->TargetIndex.find(dependee);
     assert(tii != this->TargetIndex.end());
     int dependee_index = tii->second;
@@ -400,13 +402,13 @@ cmComputeTargetDepends::DisplayGraph(Graph const& graph, const char* name)
   for(int depender_index = 0; depender_index < n; ++depender_index)
     {
     EdgeList const& nl = graph[depender_index];
-    cmTarget* depender = this->Targets[depender_index];
+    cmTarget const* depender = this->Targets[depender_index];
     fprintf(stderr, "target %d is [%s]\n",
             depender_index, depender->GetName());
     for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
       int dependee_index = *ni;
-      cmTarget* dependee = this->Targets[dependee_index];
+      cmTarget const* dependee = this->Targets[dependee_index];
       fprintf(stderr, "  depends on target %d [%s] (%s)\n", dependee_index,
               dependee->GetName(), ni->IsStrong()? "strong" : "weak");
       }
@@ -493,7 +495,7 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c,
     {
     // Get the depender.
     int i = *ci;
-    cmTarget* depender = this->Targets[i];
+    cmTarget const* depender = this->Targets[i];
 
     // Describe the depender.
     e << "  \"" << depender->GetName() << "\" of type "
@@ -506,7 +508,7 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c,
       int j = *ni;
       if(cmap[j] == c)
         {
-        cmTarget* dependee = this->Targets[j];
+        cmTarget const* dependee = this->Targets[j];
         e << "    depends on \"" << dependee->GetName() << "\""
           << " (" << (ni->IsStrong()? "strong" : "weak") << ")\n";
         }