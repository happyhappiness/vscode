@@ -170,7 +170,6 @@ items that we know the linker will re-use automatically (shared libs).
 
 */
 
-//----------------------------------------------------------------------------
 cmComputeLinkDepends
 ::cmComputeLinkDepends(const cmGeneratorTarget* target,
                        const std::string& config)
@@ -199,20 +198,17 @@ ::cmComputeLinkDepends(const cmGeneratorTarget* target,
   this->CCG = 0;
 }
 
-//----------------------------------------------------------------------------
 cmComputeLinkDepends::~cmComputeLinkDepends()
 {
   cmDeleteAll(this->InferredDependSets);
   delete this->CCG;
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::SetOldLinkDirMode(bool b)
 {
   this->OldLinkDirMode = b;
 }
 
-//----------------------------------------------------------------------------
 std::vector<cmComputeLinkDepends::LinkEntry> const&
 cmComputeLinkDepends::Compute()
 {
@@ -290,7 +286,6 @@ cmComputeLinkDepends::Compute()
   return this->FinalLinkEntries;
 }
 
-//----------------------------------------------------------------------------
 std::map<std::string, int>::iterator
 cmComputeLinkDepends::AllocateLinkEntry(std::string const& item)
 {
@@ -304,7 +299,6 @@ cmComputeLinkDepends::AllocateLinkEntry(std::string const& item)
   return lei;
 }
 
-//----------------------------------------------------------------------------
 int cmComputeLinkDepends::AddLinkEntry(cmLinkItem const& item)
 {
   // Check if the item entry has already been added.
@@ -354,7 +348,6 @@ int cmComputeLinkDepends::AddLinkEntry(cmLinkItem const& item)
   return index;
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::FollowLinkEntry(BFSEntry const& qe)
 {
   // Get this entry representation.
@@ -397,7 +390,6 @@ void cmComputeLinkDepends::FollowLinkEntry(BFSEntry const& qe)
     }
 }
 
-//----------------------------------------------------------------------------
 void
 cmComputeLinkDepends
 ::FollowSharedDeps(int depender_index, cmLinkInterface const* iface,
@@ -414,7 +406,6 @@ ::FollowSharedDeps(int depender_index, cmLinkInterface const* iface,
     }
 }
 
-//----------------------------------------------------------------------------
 void
 cmComputeLinkDepends
 ::QueueSharedDependencies(int depender_index,
@@ -430,7 +421,6 @@ ::QueueSharedDependencies(int depender_index,
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::HandleSharedDependency(SharedDepEntry const& dep)
 {
   // Check if the target already has an entry.
@@ -472,7 +462,6 @@ void cmComputeLinkDepends::HandleSharedDependency(SharedDepEntry const& dep)
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::AddVarLinkEntries(int depender_index,
                                              const char* value)
 {
@@ -550,7 +539,6 @@ void cmComputeLinkDepends::AddVarLinkEntries(int depender_index,
   this->AddLinkEntries(depender_index, actual_libs);
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::AddDirectLinkEntries()
 {
   // Add direct link dependencies in this configuration.
@@ -565,7 +553,6 @@ void cmComputeLinkDepends::AddDirectLinkEntries()
     }
 }
 
-//----------------------------------------------------------------------------
 template <typename T>
 void
 cmComputeLinkDepends::AddLinkEntries(
@@ -632,7 +619,6 @@ cmComputeLinkDepends::AddLinkEntries(
     }
 }
 
-//----------------------------------------------------------------------------
 cmGeneratorTarget const*
 cmComputeLinkDepends::FindTargetToLink(int depender_index,
                                        const std::string& name)
@@ -650,7 +636,6 @@ cmComputeLinkDepends::FindTargetToLink(int depender_index,
   return from->FindTargetToLink(name);
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::InferDependencies()
 {
   // The inferred dependency sets for each item list the possible
@@ -685,7 +670,6 @@ void cmComputeLinkDepends::InferDependencies()
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::CleanConstraintGraph()
 {
   for(Graph::iterator i = this->EntryConstraintGraph.begin();
@@ -700,7 +684,6 @@ void cmComputeLinkDepends::CleanConstraintGraph()
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::DisplayConstraintGraph()
 {
   // Display the graph nodes and their edges.
@@ -714,7 +697,6 @@ void cmComputeLinkDepends::DisplayConstraintGraph()
   fprintf(stderr, "%s\n", e.str().c_str());
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::OrderLinkEntires()
 {
   // Compute the DAG of strongly connected components.  The algorithm
@@ -765,7 +747,6 @@ void cmComputeLinkDepends::OrderLinkEntires()
     }
 }
 
-//----------------------------------------------------------------------------
 void
 cmComputeLinkDepends::DisplayComponents()
 {
@@ -793,7 +774,6 @@ cmComputeLinkDepends::DisplayComponents()
   fprintf(stderr, "\n");
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::VisitComponent(unsigned int c)
 {
   // Check if the node has already been visited.
@@ -819,7 +799,6 @@ void cmComputeLinkDepends::VisitComponent(unsigned int c)
   this->ComponentOrder[c] = --this->ComponentOrderId;
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::VisitEntry(int index)
 {
   // Include this entry on the link line.
@@ -890,7 +869,6 @@ void cmComputeLinkDepends::VisitEntry(int index)
     }
 }
 
-//----------------------------------------------------------------------------
 cmComputeLinkDepends::PendingComponent&
 cmComputeLinkDepends::MakePendingComponent(unsigned int component)
 {
@@ -928,7 +906,6 @@ cmComputeLinkDepends::MakePendingComponent(unsigned int component)
   return pc;
 }
 
-//----------------------------------------------------------------------------
 int cmComputeLinkDepends::ComputeComponentCount(NodeList const& nl)
 {
   unsigned int count = 2;
@@ -949,7 +926,6 @@ int cmComputeLinkDepends::ComputeComponentCount(NodeList const& nl)
   return count;
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::DisplayFinalEntries()
 {
   fprintf(stderr, "target [%s] links to:\n", this->Target->GetName().c_str());
@@ -969,7 +945,6 @@ void cmComputeLinkDepends::DisplayFinalEntries()
   fprintf(stderr, "\n");
 }
 
-//----------------------------------------------------------------------------
 void cmComputeLinkDepends::CheckWrongConfigItem(cmLinkItem const& item)
 {
   if(!this->OldLinkDirMode)