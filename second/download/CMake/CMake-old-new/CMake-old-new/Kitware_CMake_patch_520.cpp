@@ -16,6 +16,7 @@
 =========================================================================*/
 #include "cmComputeTargetDepends.h"
 
+#include "cmComputeComponentGraph.h"
 #include "cmGlobalGenerator.h"
 #include "cmLocalGenerator.h"
 #include "cmMakefile.h"
@@ -117,25 +118,25 @@ bool cmComputeTargetDepends::Compute()
   this->CollectDepends();
   if(this->DebugMode)
     {
-    this->DisplayGraph(this->TargetDependGraph, "initial");
+    this->DisplayGraph(this->InitialGraph, "initial");
     }
 
   // Identify components.
-  this->Tarjan();
+  cmComputeComponentGraph ccg(this->InitialGraph);
   if(this->DebugMode)
     {
-    this->DisplayComponents();
+    this->DisplayComponents(ccg);
     }
-  if(!this->CheckComponents())
+  if(!this->CheckComponents(ccg))
     {
     return false;
     }
 
   // Compute the final dependency graph.
-  this->ComputeFinalDepends();
+  this->ComputeFinalDepends(ccg);
   if(this->DebugMode)
     {
-    this->DisplayGraph(this->FinalDependGraph, "final");
+    this->DisplayGraph(this->FinalGraph, "final");
     }
 
   return true;
@@ -153,11 +154,10 @@ cmComputeTargetDepends::GetTargetDirectDepends(cmTarget* t,
   int i = tii->second;
 
   // Get its final dependencies.
-  TargetDependList const& tdl = this->FinalDependGraph[i];
-  for(TargetDependList::const_iterator di = tdl.begin();
-      di != tdl.end(); ++di)
+  NodeList const& nl = this->FinalGraph[i];
+  for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
     {
-    deps.insert(this->Targets[*di]);
+    deps.insert(this->Targets[*ni]);
     }
 }
 
@@ -184,7 +184,7 @@ void cmComputeTargetDepends::CollectTargets()
 void cmComputeTargetDepends::CollectDepends()
 {
   // Allocate the dependency graph adjacency lists.
-  this->TargetDependGraph.resize(this->Targets.size());
+  this->InitialGraph.resize(this->Targets.size());
 
   // Compute each dependency list.
   for(unsigned int i=0; i < this->Targets.size(); ++i)
@@ -265,27 +265,24 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
   int dependee_index = tii->second;
 
   // Add this entry to the dependency graph.
-  this->TargetDependGraph[depender_index].push_back(dependee_index);
+  this->InitialGraph[depender_index].push_back(dependee_index);
 }
 
 //----------------------------------------------------------------------------
 void
-cmComputeTargetDepends
-::DisplayGraph(std::vector<TargetDependList> const& graph,
-               const char* name)
+cmComputeTargetDepends::DisplayGraph(Graph const& graph, const char* name)
 {
   fprintf(stderr, "The %s target dependency graph is:\n", name);
   int n = static_cast<int>(graph.size());
   for(int depender_index = 0; depender_index < n; ++depender_index)
     {
-    TargetDependList const& tdl = graph[depender_index];
+    NodeList const& nl = graph[depender_index];
     cmTarget* depender = this->Targets[depender_index];
     fprintf(stderr, "target %d is [%s]\n",
             depender_index, depender->GetName());
-    for(TargetDependList::const_iterator di = tdl.begin();
-        di != tdl.end(); ++di)
+    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
-      int dependee_index = *di;
+      int dependee_index = *ni;
       cmTarget* dependee = this->Targets[dependee_index];
       fprintf(stderr, "  depends on target %d [%s]\n", dependee_index,
               dependee->GetName());
@@ -295,115 +292,20 @@ ::DisplayGraph(std::vector<TargetDependList> const& graph,
 }
 
 //----------------------------------------------------------------------------
-void cmComputeTargetDepends::Tarjan()
-{
-  int n = static_cast<int>(this->TargetDependGraph.size());
-  TarjanEntry entry = {0,-1,0};
-  this->TarjanEntries.resize(n, entry);
-  this->TarjanWalkId = 0;
-  this->TarjanVisited.resize(n, 0);
-  for(int i = 0; i < n; ++i)
-    {
-    // Start a new DFS from this node if it has never been visited.
-    if(!this->TarjanVisited[i])
-      {
-      assert(this->TarjanStack.empty());
-      ++this->TarjanWalkId;
-      this->TarjanIndex = 0;
-      this->TarjanVisit(i);
-      }
-    }
-}
-
-//----------------------------------------------------------------------------
-void cmComputeTargetDepends::TarjanVisit(int i)
-{
-  // We are now visiting this node.
-  this->TarjanVisited[i] = this->TarjanWalkId;
-
-  // Initialize the entry.
-  this->TarjanEntries[i].Root = i;
-  this->TarjanEntries[i].Component = -1;
-  this->TarjanEntries[i].VisitIndex = ++this->TarjanIndex;
-  this->TarjanStack.push(i);
-
-  // Follow outgoing edges.
-  TargetDependList const& tdl = this->TargetDependGraph[i];
-  for(TargetDependList::const_iterator di = tdl.begin();
-      di != tdl.end(); ++di)
-    {
-    int j = *di;
-
-    // Ignore edges to nodes that have been reached by a previous DFS
-    // walk.  Since we did not reach the current node from that walk
-    // it must not belong to the same component and it has already
-    // been assigned to a component.
-    if(this->TarjanVisited[j] > 0 &&
-       this->TarjanVisited[j] < this->TarjanWalkId)
-      {
-      continue;
-      }
-
-    // Visit the destination if it has not yet been visited.
-    if(!this->TarjanVisited[j])
-      {
-      this->TarjanVisit(j);
-      }
-
-    // If the destination has not yet been assigned to a component,
-    // check if it is a better potential root for the current object.
-    if(this->TarjanEntries[j].Component < 0)
-      {
-      if(this->TarjanEntries[this->TarjanEntries[j].Root].VisitIndex <
-         this->TarjanEntries[this->TarjanEntries[i].Root].VisitIndex)
-        {
-        this->TarjanEntries[i].Root = this->TarjanEntries[j].Root;
-        }
-      }
-    }
-
-  // Check if we have found a component.
-  if(this->TarjanEntries[i].Root == i)
-    {
-    // Yes.  Create it.
-    int c = static_cast<int>(this->Components.size());
-    this->Components.push_back(ComponentList());
-    ComponentList& component = this->Components[c];
-
-    // Populate the component list.
-    int j;
-    do
-      {
-      // Get the next member of the component.
-      j = this->TarjanStack.top();
-      this->TarjanStack.pop();
-
-      // Assign the member to the component.
-      this->TarjanEntries[j].Component = c;
-      this->TarjanEntries[j].Root = i;
-
-      // Store the node in its component.
-      component.push_back(j);
-      } while(j != i);
-
-    // Sort the component members for clarity.
-    std::sort(component.begin(), component.end());
-    }
-}
-
-//----------------------------------------------------------------------------
-void cmComputeTargetDepends::DisplayComponents()
+void
+cmComputeTargetDepends
+::DisplayComponents(cmComputeComponentGraph const& ccg)
 {
   fprintf(stderr, "The strongly connected components are:\n");
-  int n = static_cast<int>(this->Components.size());
+  std::vector<NodeList> const& components = ccg.GetComponents();
+  int n = static_cast<int>(components.size());
   for(int c = 0; c < n; ++c)
     {
-    ComponentList const& cl = this->Components[c];
+    NodeList const& nl = components[c];
     fprintf(stderr, "Component (%d):\n", c);
-    for(ComponentList::const_iterator ci = cl.begin();
-        ci != cl.end(); ++ci)
+    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
-      int i = *ci;
+      int i = *ni;
       fprintf(stderr, "  contains target %d [%s]\n",
               i, this->Targets[i]->GetName());
       }
@@ -412,28 +314,31 @@ void cmComputeTargetDepends::DisplayComponents()
 }
 
 //----------------------------------------------------------------------------
-bool cmComputeTargetDepends::CheckComponents()
+bool
+cmComputeTargetDepends
+::CheckComponents(cmComputeComponentGraph const& ccg)
 {
   // All non-trivial components should consist only of static
   // libraries.
-  int nc = static_cast<int>(this->Components.size());
+  std::vector<NodeList> const& components = ccg.GetComponents();
+  int nc = static_cast<int>(components.size());
   for(int c=0; c < nc; ++c)
     {
     // Get the current component.
-    ComponentList const& cl = this->Components[c];
+    NodeList const& nl = components[c];
 
     // Skip trivial components.
-    if(cl.size() < 2)
+    if(nl.size() < 2)
       {
       continue;
       }
 
     // Make sure the component is all STATIC_LIBRARY targets.
-    for(ComponentList::const_iterator ci = cl.begin(); ci != cl.end(); ++ci)
+    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
-      if(this->Targets[*ci]->GetType() != cmTarget::STATIC_LIBRARY)
+      if(this->Targets[*ni]->GetType() != cmTarget::STATIC_LIBRARY)
         {
-        this->ComplainAboutBadComponent(c);
+        this->ComplainAboutBadComponent(ccg, c);
         return false;
         }
       }
@@ -443,16 +348,17 @@ bool cmComputeTargetDepends::CheckComponents()
 
 //----------------------------------------------------------------------------
 void
-cmComputeTargetDepends::ComplainAboutBadComponent(int c)
+cmComputeTargetDepends
+::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c)
 {
-  // Get the bad component.
-  ComponentList const& cl = this->Components[c];
-
   // Construct the error message.
   cmOStringStream e;
   e << "The inter-target dependency graph contains the following "
     << "strongly connected component (cycle):\n";
-  for(ComponentList::const_iterator ci = cl.begin(); ci != cl.end(); ++ci)
+  std::vector<NodeList> const& components = ccg.GetComponents();
+  std::vector<int> const& cmap = ccg.GetComponentMap();
+  NodeList const& cl = components[c];
+  for(NodeList::const_iterator ci = cl.begin(); ci != cl.end(); ++ci)
     {
     // Get the depender.
     int i = *ci;
@@ -463,12 +369,11 @@ cmComputeTargetDepends::ComplainAboutBadComponent(int c)
       << cmTarget::TargetTypeNames[depender->GetType()] << "\n";
 
     // List its dependencies that are inside the component.
-    TargetDependList const& tdl = this->TargetDependGraph[i];
-    for(TargetDependList::const_iterator di = tdl.begin();
-        di != tdl.end(); ++di)
+    NodeList const& nl = this->InitialGraph[i];
+    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
-      int j = *di;
-      if(this->TarjanEntries[j].Component == c)
+      int j = *ni;
+      if(cmap[j] == c)
         {
         cmTarget* dependee = this->Targets[j];
         e << "    depends on " << dependee->GetName() << "\n";
@@ -481,46 +386,45 @@ cmComputeTargetDepends::ComplainAboutBadComponent(int c)
 }
 
 //----------------------------------------------------------------------------
-void cmComputeTargetDepends::ComputeFinalDepends()
+void
+cmComputeTargetDepends
+::ComputeFinalDepends(cmComputeComponentGraph const& ccg)
 {
-  int n = static_cast<int>(this->TargetDependGraph.size());
-  this->FinalDependGraph.resize(n);
+  // Get the component graph information.
+  std::vector<NodeList> const& components = ccg.GetComponents();
+  Graph const& cgraph = ccg.GetComponentGraph();
+
+  // Allocate the final graph.
+  this->FinalGraph.resize(0);
+  this->FinalGraph.resize(this->InitialGraph.size());
 
   // Convert inter-component edges to connect component tails to heads.
-  for(int i=0; i < n; ++i)
+  int n = static_cast<int>(cgraph.size());
+  for(int depender_component=0; depender_component < n; ++depender_component)
     {
-    int depender_component = this->TarjanEntries[i].Component;
-    int depender_component_tail =
-      this->Components[depender_component].back();
-
-    TargetDependList const& tdl = this->TargetDependGraph[i];
-    for(TargetDependList::const_iterator di = tdl.begin();
-        di != tdl.end(); ++di)
+    int depender_component_tail = components[depender_component].back();
+    NodeList const& nl = cgraph[depender_component];
+    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
-      int j = *di;
-      int dependee_component = this->TarjanEntries[j].Component;
-      int dependee_component_head =
-        this->Components[dependee_component].front();
-      if(depender_component != dependee_component)
-        {
-        this->FinalDependGraph[depender_component_tail]
-          .push_back(dependee_component_head);
-        }
+      int dependee_component = *ni;
+      int dependee_component_head = components[dependee_component].front();
+      this->FinalGraph[depender_component_tail]
+        .push_back(dependee_component_head);
       }
     }
 
   // Compute intra-component edges.
-  int nc = static_cast<int>(this->Components.size());
+  int nc = static_cast<int>(components.size());
   for(int c=0; c < nc; ++c)
     {
     // Within the component each target depends on that following it.
-    ComponentList const& cl = this->Components[c];
-    ComponentList::const_iterator ci = cl.begin();
-    int last_i = *ci;
-    for(++ci; ci != cl.end(); ++ci)
+    NodeList const& nl = components[c];
+    NodeList::const_iterator ni = nl.begin();
+    int last_i = *ni;
+    for(++ni; ni != nl.end(); ++ni)
       {
-      int i = *ci;
-      this->FinalDependGraph[last_i].push_back(i);
+      int i = *ni;
+      this->FinalGraph[last_i].push_back(i);
       last_i = i;
       }
     }