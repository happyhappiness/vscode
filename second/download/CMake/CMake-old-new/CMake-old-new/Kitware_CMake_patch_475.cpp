@@ -129,7 +129,10 @@ bool cmComputeTargetDepends::Compute()
     }
 
   // Compute the final dependency graph.
-  this->ComputeFinalDepends(ccg);
+  if(!this->ComputeFinalDepends(ccg))
+    {
+    return false;
+    }
   if(this->DebugMode)
     {
     this->DisplayGraph(this->FinalGraph, "final");
@@ -150,8 +153,8 @@ cmComputeTargetDepends::GetTargetDirectDepends(cmTarget* t,
   int i = tii->second;
 
   // Get its final dependencies.
-  NodeList const& nl = this->FinalGraph[i];
-  for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+  EdgeList const& nl = this->FinalGraph[i];
+  for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
     {
     deps.insert(this->Targets[*ni]);
     }
@@ -195,15 +198,13 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
   // Get the depender.
   cmTarget* depender = this->Targets[depender_index];
 
-  // Keep track of dependencies already listed.
-  std::set<cmStdString> emitted;
-
-  // A target should not depend on itself.
-  emitted.insert(depender->GetName());
-
   // Loop over all targets linked directly.
+  {
   cmTarget::LinkLibraryVectorType const& tlibs =
     depender->GetOriginalLinkLibraries();
+  std::set<cmStdString> emitted;
+  // A target should not depend on itself.
+  emitted.insert(depender->GetName());
   for(cmTarget::LinkLibraryVectorType::const_iterator lib = tlibs.begin();
       lib != tlibs.end(); ++lib)
     {
@@ -213,9 +214,14 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
       this->AddTargetDepend(depender_index, lib->first.c_str(), true);
       }
     }
+  }
 
   // Loop over all utility dependencies.
+  {
   std::set<cmStdString> const& tutils = depender->GetUtilities();
+  std::set<cmStdString> emitted;
+  // A target should not depend on itself.
+  emitted.insert(depender->GetName());
   for(std::set<cmStdString>::const_iterator util = tutils.begin();
       util != tutils.end(); ++util)
     {
@@ -225,6 +231,7 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
       this->AddTargetDepend(depender_index, util->c_str(), false);
       }
     }
+  }
 }
 
 //----------------------------------------------------------------------------
@@ -272,7 +279,8 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
   int dependee_index = tii->second;
 
   // Add this entry to the dependency graph.
-  this->InitialGraph[depender_index].push_back(dependee_index);
+  this->InitialGraph[depender_index].push_back(
+    cmGraphEdge(dependee_index, !linking));
 }
 
 //----------------------------------------------------------------------------
@@ -283,16 +291,16 @@ cmComputeTargetDepends::DisplayGraph(Graph const& graph, const char* name)
   int n = static_cast<int>(graph.size());
   for(int depender_index = 0; depender_index < n; ++depender_index)
     {
-    NodeList const& nl = graph[depender_index];
+    EdgeList const& nl = graph[depender_index];
     cmTarget* depender = this->Targets[depender_index];
     fprintf(stderr, "target %d is [%s]\n",
             depender_index, depender->GetName());
-    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+    for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
       int dependee_index = *ni;
       cmTarget* dependee = this->Targets[dependee_index];
-      fprintf(stderr, "  depends on target %d [%s]\n", dependee_index,
-              dependee->GetName());
+      fprintf(stderr, "  depends on target %d [%s] (%s)\n", dependee_index,
+              dependee->GetName(), ni->IsStrong()? "strong" : "weak");
       }
     }
   fprintf(stderr, "\n");
@@ -363,7 +371,8 @@ ::CheckComponents(cmComputeComponentGraph const& ccg)
 //----------------------------------------------------------------------------
 void
 cmComputeTargetDepends
-::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c)
+::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c,
+                            bool strong)
 {
   // Construct the error message.
   cmOStringStream e;
@@ -383,18 +392,27 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c)
       << cmTarget::TargetTypeNames[depender->GetType()] << "\n";
 
     // List its dependencies that are inside the component.
-    NodeList const& nl = this->InitialGraph[i];
-    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+    EdgeList const& nl = this->InitialGraph[i];
+    for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
       int j = *ni;
       if(cmap[j] == c)
         {
         cmTarget* dependee = this->Targets[j];
-        e << "    depends on \"" << dependee->GetName() << "\"\n";
+        e << "    depends on \"" << dependee->GetName() << "\""
+          << " (" << (ni->IsStrong()? "strong" : "weak") << ")\n";
         }
       }
     }
-  if(this->NoCycles)
+  if(strong)
+    {
+    // Custom command executable dependencies cannot occur within a
+    // component of static libraries.  The cycle must appear in calls
+    // to add_dependencies.
+    e << "The component contains at least one cycle consisting of strong "
+      << "dependencies (created by add_dependencies) that cannot be broken.";
+    }
+  else if(this->NoCycles)
     {
     e << "The GLOBAL_DEPENDS_NO_CYCLES global property is enabled, so "
       << "cyclic dependencies are not allowed even among static libraries.";
@@ -408,7 +426,49 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c)
 }
 
 //----------------------------------------------------------------------------
-void
+bool
+cmComputeTargetDepends
+::IntraComponent(std::vector<int> const& cmap, int c, int i, int* head,
+                 std::set<int>& emitted, std::set<int>& visited)
+{
+  if(!visited.insert(i).second)
+    {
+    // Cycle in utility depends!
+    return false;
+    }
+  if(emitted.insert(i).second)
+    {
+    // Honor strong intra-component edges in the final order.
+    EdgeList const& el = this->InitialGraph[i];
+    for(EdgeList::const_iterator ei = el.begin(); ei != el.end(); ++ei)
+      {
+      int j = *ei;
+      if(cmap[j] == c && ei->IsStrong())
+        {
+        this->FinalGraph[i].push_back(j);
+        if(!this->IntraComponent(cmap, c, j, head, emitted, visited))
+          {
+          return false;
+          }
+        }
+      }
+
+    // Prepend to a linear linked-list of intra-component edges.
+    if(*head >= 0)
+      {
+      this->FinalGraph[i].push_back(*head);
+      }
+    else
+      {
+      this->ComponentTail[c] = i;
+      }
+    *head = i;
+    }
+  return true;
+}
+
+//----------------------------------------------------------------------------
+bool
 cmComputeTargetDepends
 ::ComputeFinalDepends(cmComputeComponentGraph const& ccg)
 {
@@ -420,34 +480,43 @@ ::ComputeFinalDepends(cmComputeComponentGraph const& ccg)
   this->FinalGraph.resize(0);
   this->FinalGraph.resize(this->InitialGraph.size());
 
+  // Choose intra-component edges to linearize dependencies.
+  std::vector<int> const& cmap = ccg.GetComponentMap();
+  this->ComponentHead.resize(components.size());
+  this->ComponentTail.resize(components.size());
+  int nc = static_cast<int>(components.size());
+  for(int c=0; c < nc; ++c)
+    {
+    int head = -1;
+    std::set<int> emitted;
+    NodeList const& nl = components[c];
+    for(NodeList::const_reverse_iterator ni = nl.rbegin();
+        ni != nl.rend(); ++ni)
+      {
+      std::set<int> visited;
+      if(!this->IntraComponent(cmap, c, *ni, &head, emitted, visited))
+        {
+        // Cycle in add_dependencies within component!
+        this->ComplainAboutBadComponent(ccg, c, true);
+        return false;
+        }
+      }
+    this->ComponentHead[c] = head;
+    }
+
   // Convert inter-component edges to connect component tails to heads.
   int n = static_cast<int>(cgraph.size());
   for(int depender_component=0; depender_component < n; ++depender_component)
     {
-    int depender_component_tail = components[depender_component].back();
-    NodeList const& nl = cgraph[depender_component];
-    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+    int depender_component_tail = this->ComponentTail[depender_component];
+    EdgeList const& nl = cgraph[depender_component];
+    for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
       int dependee_component = *ni;
-      int dependee_component_head = components[dependee_component].front();
+      int dependee_component_head = this->ComponentHead[dependee_component];
       this->FinalGraph[depender_component_tail]
         .push_back(dependee_component_head);
       }
     }
-
-  // Compute intra-component edges.
-  int nc = static_cast<int>(components.size());
-  for(int c=0; c < nc; ++c)
-    {
-    // Within the component each target depends on that following it.
-    NodeList const& nl = components[c];
-    NodeList::const_iterator ni = nl.begin();
-    int last_i = *ni;
-    for(++ni; ni != nl.end(); ++ni)
-      {
-      int i = *ni;
-      this->FinalGraph[last_i].push_back(i);
-      last_i = i;
-      }
-    }
+  return true;
 }