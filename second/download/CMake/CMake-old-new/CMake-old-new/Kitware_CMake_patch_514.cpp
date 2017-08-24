@@ -33,10 +33,10 @@ This file computes an ordered list of link items to use when linking a
 single target in one configuration.  Each link item is identified by
 the string naming it.  A graph of dependencies is created in which
 each node corresponds to one item and directed eges lead from nodes to
-those which must *precede* them on the link line.  For example, the
+those which must *follow* them on the link line.  For example, the
 graph
 
-  C -> B -> A
+  A -> B -> C
 
 will lead to the link line order
 
@@ -65,11 +65,11 @@ items X and Y are known, then we might have the following dependency
 
 The explicitly known dependencies form graph edges
 
-  X <- Y  ,  X <- A  ,  X <- B  ,  Y <- A  ,  Y <- B
+  X -> Y  ,  X -> A  ,  X -> B  ,  Y -> A  ,  Y -> B
 
 We can also infer the edge
 
-  A <- B
+  A -> B
 
 because *every* time A appears B is seen on its right.  We do not know
 whether A really needs symbols from B to link, but it *might* so we
@@ -93,12 +93,12 @@ considering these dependency lists:
 
 The explicit edges are
 
-  X <- Y  ,  X <- A  ,  X <- B  ,  X <- C  ,  Y <- A  ,  Y <- B  ,  Y <- C
+  X -> Y  ,  X -> A  ,  X -> B  ,  X -> C  ,  Y -> A  ,  Y -> B  ,  Y -> C
 
 For the unknown items, we infer dependencies by looking at the
 "follow" sets:
 
-  A: intersect( {B,Y,C} , {C,B} ) = {B,C} ; infer edges  A <- B  ,  A <- C
+  A: intersect( {B,Y,C} , {C,B} ) = {B,C} ; infer edges  A -> B  ,  A -> C
   B: intersect( {Y,C}   , {}    ) = {}    ; infer no edges
   C: intersect( {}      , {B}   ) = {}    ; infer no edges
 
@@ -107,57 +107,71 @@ libraries should not depend on them.
 
 ------------------------------------------------------------------------------
 
-Once the complete graph is formed from all known and inferred
-dependencies we must use it to produce a valid link line.  If the
-dependency graph were known to be acyclic a simple depth-first-search
-would produce a correct link line.  Unfortunately we cannot make this
-assumption so the following technique is used.
+The initial exploration of dependencies using a BFS associates an
+integer index with each link item.  When the graph is built outgoing
+edges are sorted by this index.
+
+After the initial exploration of the link interface tree, any
+transitive (dependent) shared libraries that were encountered and not
+included in the interface are processed in their own BFS.  This BFS
+follows only the dependent library lists and not the link interfaces.
+They are added to the link items with a mark indicating that the are
+transitive dependencies.  Then cmComputeLinkInformation deals with
+them on a per-platform basis.
 
+The complete graph formed from all known and inferred dependencies may
+not be acyclic, so an acyclic version must be created.
 The original graph is converted to a directed acyclic graph in which
 each node corresponds to a strongly connected component of the
 original graph.  For example, the dependency graph
 
-  X <- A <- B <- C <- A <- Y
+  X -> A -> B -> C -> A -> Y
 
 contains strongly connected components {X}, {A,B,C}, and {Y}.  The
 implied directed acyclic graph (DAG) is
 
-  {X} <- {A,B,C} <- {Y}
-
-The final list of link items is constructed by a series of
-depth-first-searches through this DAG of components.  When visiting a
-component all outgoing edges are followed first because the neighbors
-must precede it.  Once neighbors across all edges have been emitted it
-is safe to emit the current component.
+  {X} -> {A,B,C} -> {Y}
 
-Trivial components (those with one item) are handled simply by
-emitting the item.  Non-trivial components (those with more than one
-item) are assumed to consist only of static libraries that may be
-safely repeated on the link line.  We emit members of the component
-multiple times (see code below for details).  The final link line for
-the example graph might be
-
-  X A B C A B C Y
+We then compute a topological order for the DAG nodes to serve as a
+reference for satisfying dependencies efficiently.  We perform the DFS
+in reverse order and assign topological order indices counting down so
+that the result is as close to the original BFS order as possible
+without violating dependencies.
 
 ------------------------------------------------------------------------------
 
-The initial exploration of dependencies using a BFS associates an
-integer index with each link item.  When the graph is built outgoing
-edges are sorted by this index.
-
-This preserves the original link order as much as possible subject to
-the dependencies.  We then further preserve the original link line by
-appending items to make sure all those that might be static libraries
-appear in the order and multiplicity that they do in the original
-line.
-
-After the initial exploration of the link interface tree, any
-transitive (dependent) shared libraries that were encountered and not
-included in the interface are processed in their own BFS.  This BFS
-follows only the dependent library lists and not the link interfaces.
-They are added to the link items with a mark indicating that the are
-transitive dependencies.  Then cmComputeLinkInformation deals with
-them on a per-platform basis.
+The final link entry order is constructed as follows.  We first walk
+through and emit the *original* link line as specified by the user.
+As each item is emitted, a set of pending nodes in the component DAG
+is maintained.  When a pending component has been completely seen, it
+is removed from the pending set and its dependencies (following edges
+of the DAG) are added.  A trivial component (those with one item) is
+complete as soon as its item is seen.  A non-trivial component (one
+with more than one item; assumed to be static libraries) is complete
+when *all* its entries have been seen *twice* (all entries seen once,
+then all entries seen again, not just each entry twice).  A pending
+component tracks which items have been seen and a count of how many
+times the component needs to be seen (once for trivial components,
+twice for non-trivial).  If at any time another component finishes and
+re-adds an already pending component, the pending component is reset
+so that it needs to be seen in its entirety again.  This ensures that
+all dependencies of a component are satisified no matter where it
+appears.
+
+After the original link line has been completed, we append to it the
+remaining pending components and their dependencies.  This is done by
+repeatedly emitting the first item from the first pending component
+and following the same update rules as when traversing the original
+link line.  Since the pending components are kept in topological order
+they are emitted with minimal repeats (we do not want to emit a
+component just to have it added again when another component is
+completed later).  This process continues until no pending components
+remain.  We know it will terminate because the component graph is
+guaranteed to be acyclic.
+
+The final list of items produced by this procedure consists of the
+original user link line followed by minimal additional items needed to
+satisfy dependencies.
 
 */
 
@@ -180,6 +194,9 @@ ::cmComputeLinkDepends(cmTarget* target, const char* config)
 
   // Assume no compatibility until set.
   this->OldLinkDirMode = false;
+
+  // No computation has been done.
+  this->CCG = 0;
 }
 
 //----------------------------------------------------------------------------
@@ -191,6 +208,7 @@ cmComputeLinkDepends::~cmComputeLinkDepends()
     {
     delete *i;
     }
+  delete this->CCG;
 }
 
 //----------------------------------------------------------------------------
@@ -244,7 +262,6 @@ cmComputeLinkDepends::Compute()
 
   // Compute the final ordering.
   this->OrderLinkEntires();
-  this->PreserveOriginalEntries();
 
   // Compute the final set of link entries.
   for(std::vector<int>::const_iterator li = this->FinalLinkOrder.begin();
@@ -402,9 +419,9 @@ void cmComputeLinkDepends::HandleSharedDependency(SharedDepEntry const& dep)
   int index = lei->second;
   LinkEntry& entry = this->EntryList[index];
 
-  // This shared library dependency must be preceded by the item that
-  // listed it.
-  this->EntryConstraintGraph[index].push_back(dep.DependerIndex);
+  // This shared library dependency must follow the item that listed
+  // it.
+  this->EntryConstraintGraph[dep.DependerIndex].push_back(index);
 
   // Target items may have their own dependencies.
   if(entry.Target)
@@ -555,12 +572,12 @@ cmComputeLinkDepends::AddLinkEntries(int depender_index,
     // Add a link entry for this item.
     int dependee_index = this->AddLinkEntry(item);
 
-    // The depender must come before the dependee.
+    // The dependee must come after the depender.
     if(depender_index >= 0)
       {
       if(!this->EntryList[dependee_index].IsFlag)
         {
-        this->EntryConstraintGraph[dependee_index].push_back(depender_index);
+        this->EntryConstraintGraph[depender_index].push_back(dependee_index);
         }
       }
     else
@@ -713,7 +730,7 @@ void cmComputeLinkDepends::InferDependencies()
     for(DependSet::const_iterator j = common.begin(); j != common.end(); ++j)
       {
       int dependee_index = *j;
-      this->EntryConstraintGraph[dependee_index].push_back(depender_index);
+      this->EntryConstraintGraph[depender_index].push_back(dependee_index);
       }
     }
 }
@@ -745,7 +762,7 @@ void cmComputeLinkDepends::DisplayConstraintGraph()
     e << "item " << i << " is [" << this->EntryList[i].Item << "]\n";
     for(NodeList::const_iterator j = nl.begin(); j != nl.end(); ++j)
       {
-      e << "  item " << *j << " must precede it\n";
+      e << "  item " << *j << " must follow it\n";
       }
     }
   fprintf(stderr, "%s\n", e.str().c_str());
@@ -759,30 +776,55 @@ void cmComputeLinkDepends::OrderLinkEntires()
   // the same order in which the items were originally discovered in
   // the BFS.  This should preserve the original order when no
   // constraints disallow it.
-  cmComputeComponentGraph ccg(this->EntryConstraintGraph);
-  Graph const& cgraph = ccg.GetComponentGraph();
+  this->CCG = new cmComputeComponentGraph(this->EntryConstraintGraph);
+
+  // The component graph is guaranteed to be acyclic.  Start a DFS
+  // from every entry to compute a topological order for the
+  // components.
+  Graph const& cgraph = this->CCG->GetComponentGraph();
+  int n = static_cast<int>(cgraph.size());
+  this->ComponentVisited.resize(cgraph.size(), 0);
+  this->ComponentOrder.resize(cgraph.size(), n);
+  this->ComponentOrderId = n;
+  // Run in reverse order so the topological order will preserve the
+  // original order where there are no constraints.
+  for(int c = n-1; c >= 0; --c)
+    {
+    this->VisitComponent(c);
+    }
+
+  // Display the component graph.
   if(this->DebugMode)
     {
-    this->DisplayComponents(ccg);
+    this->DisplayComponents();
     }
 
-  // Setup visit tracking.
-  this->ComponentVisited.resize(cgraph.size(), 0);
+  // Start with the original link line.
+  for(std::vector<int>::const_iterator i = this->OriginalEntries.begin();
+      i != this->OriginalEntries.end(); ++i)
+    {
+    this->VisitEntry(*i);
+    }
 
-  // The component graph is guaranteed to be acyclic.  Start a DFS
-  // from every entry.
-  for(unsigned int c=0; c < cgraph.size(); ++c)
+  // Now explore anything left pending.  Since the component graph is
+  // guaranteed to be acyclic we know this will terminate.
+  while(!this->PendingComponents.empty())
     {
-    this->VisitComponent(ccg, c);
+    // Visit one entry from the first pending component.  The visit
+    // logic will update the pending components accordingly.  Since
+    // the pending components are kept in topological order this will
+    // not repeat one.
+    int e = *this->PendingComponents.begin()->second.Entries.begin();
+    this->VisitEntry(e);
     }
 }
 
 //----------------------------------------------------------------------------
 void
-cmComputeLinkDepends::DisplayComponents(cmComputeComponentGraph const& ccg)
+cmComputeLinkDepends::DisplayComponents()
 {
   fprintf(stderr, "The strongly connected components are:\n");
-  std::vector<NodeList> const& components = ccg.GetComponents();
+  std::vector<NodeList> const& components = this->CCG->GetComponents();
   for(unsigned int c=0; c < components.size(); ++c)
     {
     fprintf(stderr, "Component (%u):\n", c);
@@ -793,14 +835,19 @@ cmComputeLinkDepends::DisplayComponents(cmComputeComponentGraph const& ccg)
       fprintf(stderr, "  item %d [%s]\n", i,
               this->EntryList[i].Item.c_str());
       }
+    NodeList const& ol = this->CCG->GetComponentGraphEdges(c);
+    for(NodeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
+      {
+      fprintf(stderr, "  followed by Component (%d)\n", *oi);
+      }
+    fprintf(stderr, "  topo order index %d\n",
+            this->ComponentOrder[c]);
     }
   fprintf(stderr, "\n");
 }
 
 //----------------------------------------------------------------------------
-void
-cmComputeLinkDepends::VisitComponent(cmComputeComponentGraph const& ccg,
-                                     unsigned int c)
+void cmComputeLinkDepends::VisitComponent(unsigned int c)
 {
   // Check if the node has already been visited.
   if(this->ComponentVisited[c])
@@ -812,49 +859,126 @@ cmComputeLinkDepends::VisitComponent(cmComputeComponentGraph const& ccg,
   this->ComponentVisited[c] = 1;
 
   // Visit the neighbors of the component first.
-  NodeList const& nl = ccg.GetComponentGraphEdges(c);
-  for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+  // Run in reverse order so the topological order will preserve the
+  // original order where there are no constraints.
+  NodeList const& nl = this->CCG->GetComponentGraphEdges(c);
+  for(NodeList::const_reverse_iterator ni = nl.rbegin();
+      ni != nl.rend(); ++ni)
     {
-    this->VisitComponent(ccg, *ni);
+    this->VisitComponent(*ni);
     }
 
-  // Now that all items required to come before this one have been
-  // emmitted, emit this component's items.
-  this->EmitComponent(ccg.GetComponent(c));
+  // Assign an ordering id to this component.
+  this->ComponentOrder[c] = --this->ComponentOrderId;
 }
 
 //----------------------------------------------------------------------------
-void cmComputeLinkDepends::EmitComponent(NodeList const& nl)
+void cmComputeLinkDepends::VisitEntry(int index)
 {
-  assert(!nl.empty());
+  // Include this entry on the link line.
+  this->FinalLinkOrder.push_back(index);
+
+  // This entry has now been seen.  Update its component.
+  bool completed = false;
+  int component = this->CCG->GetComponentMap()[index];
+  std::map<int, PendingComponent>::iterator mi =
+    this->PendingComponents.find(this->ComponentOrder[component]);
+  if(mi != this->PendingComponents.end())
+    {
+    // The entry is in an already pending component.
+    PendingComponent& pc = mi->second;
+
+    // Remove the entry from those pending in its component.
+    pc.Entries.erase(index);
+    if(pc.Entries.empty())
+      {
+      // The complete component has been seen since it was last needed.
+      --pc.Count;
 
-  // Handle trivial components.
-  if(nl.size() == 1)
+      if(pc.Count == 0)
+        {
+        // The component has been completed.
+        this->PendingComponents.erase(mi);
+        completed = true;
+        }
+      else
+        {
+        // The whole component needs to be seen again.
+        NodeList const& nl = this->CCG->GetComponent(component);
+        assert(nl.size() > 1);
+        pc.Entries.insert(nl.begin(), nl.end());
+        }
+      }
+    }
+  else
     {
-    this->FinalLinkOrder.push_back(nl[0]);
-    return;
+    // The entry is not in an already pending component.
+    NodeList const& nl = this->CCG->GetComponent(component);
+    if(nl.size() > 1)
+      {
+      // This is a non-trivial component.  It is now pending.
+      PendingComponent& pc = this->MakePendingComponent(component);
+
+      // The starting entry has already been seen.
+      pc.Entries.erase(index);
+      }
+    else
+      {
+      // This is a trivial component, so it is already complete.
+      completed = true;
+      }
     }
 
-  // This is a non-trivial strongly connected component of the
-  // original graph.  It consists of two or more libraries (archives)
-  // that mutually require objects from one another.  In the worst
-  // case we may have to repeat the list of libraries as many times as
-  // there are object files in the biggest archive.  For now we just
-  // list them twice.
-  //
-  // The list of items in the component has been sorted by the order
-  // of discovery in the original BFS of dependencies.  This has the
-  // advantage that the item directly linked by a target requiring
-  // this component will come first which minimizes the number of
-  // repeats needed.
-  for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+  // If the entry completed a component, the component's dependencies
+  // are now pending.
+  if(completed)
     {
-    this->FinalLinkOrder.push_back(*ni);
+    NodeList const& ol = this->CCG->GetComponentGraphEdges(component);
+    for(NodeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
+      {
+      // This entire component is now pending no matter whether it has
+      // been partially seen already.
+      this->MakePendingComponent(*oi);
+      }
     }
-  for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+}
+
+//----------------------------------------------------------------------------
+cmComputeLinkDepends::PendingComponent&
+cmComputeLinkDepends::MakePendingComponent(unsigned int component)
+{
+  // Create an entry (in topological order) for the component.
+  PendingComponent& pc =
+    this->PendingComponents[this->ComponentOrder[component]];
+  pc.Id = component;
+  NodeList const& nl = this->CCG->GetComponent(component);
+
+  if(nl.size() == 1)
     {
-    this->FinalLinkOrder.push_back(*ni);
+    // Trivial components need be seen only once.
+    pc.Count = 1;
     }
+  else
+    {
+    // This is a non-trivial strongly connected component of the
+    // original graph.  It consists of two or more libraries
+    // (archives) that mutually require objects from one another.  In
+    // the worst case we may have to repeat the list of libraries as
+    // many times as there are object files in the biggest archive.
+    // For now we just list them twice.
+    //
+    // The list of items in the component has been sorted by the order
+    // of discovery in the original BFS of dependencies.  This has the
+    // advantage that the item directly linked by a target requiring
+    // this component will come first which minimizes the number of
+    // repeats needed.
+    pc.Count = 2;
+    }
+
+  // Store the entries to be seen.
+  pc.Entries.insert(nl.begin(), nl.end());
+
+  return pc;
 }
 
 //----------------------------------------------------------------------------
@@ -896,57 +1020,3 @@ void cmComputeLinkDepends::CheckWrongConfigItem(std::string const& item)
       }
     }
 }
-
-//----------------------------------------------------------------------------
-static bool cmComputeLinkDependsNotStatic(cmTarget* tgt)
-{
-  return (tgt &&
-          tgt->GetType() != cmTarget::STATIC_LIBRARY &&
-          tgt->GetType() != cmTarget::UNKNOWN_LIBRARY);
-}
-
-//----------------------------------------------------------------------------
-void cmComputeLinkDepends::PreserveOriginalEntries()
-{
-  // Skip the part of the input sequence that already appears in the
-  // output.
-  std::vector<int>::const_iterator in = this->OriginalEntries.begin();
-  std::vector<int>::const_iterator out = this->FinalLinkOrder.begin();
-  while(in != this->OriginalEntries.end() &&
-        out != this->FinalLinkOrder.end())
-    {
-    cmTarget* tgt = this->EntryList[*in].Target;
-    if(cmComputeLinkDependsNotStatic(tgt))
-      {
-      // Skip input items known to not be static libraries.
-      ++in;
-      }
-    else if(*in == *out)
-      {
-      // The input and output items match.  Move on to the next items.
-      ++in;
-      ++out;
-      }
-    else
-      {
-      // The output item does not match the next input item.  Skip it.
-      ++out;
-      }
-    }
-
-  // Append the part of the input sequence that does not already
-  // appear in the output.
-  while(in != this->OriginalEntries.end())
-    {
-    cmTarget* tgt = this->EntryList[*in].Target;
-    if(cmComputeLinkDependsNotStatic(tgt))
-      {
-      // Skip input items known to not be static libraries.
-      ++in;
-      }
-    else
-      {
-      this->FinalLinkOrder.push_back(*in++);
-      }
-    }
-}