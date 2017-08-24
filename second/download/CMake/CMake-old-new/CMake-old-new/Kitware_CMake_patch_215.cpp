@@ -94,7 +94,6 @@ transitively on all the static libraries it links.
 
 */
 
-//----------------------------------------------------------------------------
 cmComputeTargetDepends::cmComputeTargetDepends(cmGlobalGenerator* gg)
 {
   this->GlobalGenerator = gg;
@@ -105,12 +104,10 @@ cmComputeTargetDepends::cmComputeTargetDepends(cmGlobalGenerator* gg)
                       ->GetGlobalPropertyAsBool("GLOBAL_DEPENDS_NO_CYCLES");
 }
 
-//----------------------------------------------------------------------------
 cmComputeTargetDepends::~cmComputeTargetDepends()
 {
 }
 
-//----------------------------------------------------------------------------
 bool cmComputeTargetDepends::Compute()
 {
   // Build the original graph.
@@ -145,7 +142,6 @@ bool cmComputeTargetDepends::Compute()
   return true;
 }
 
-//----------------------------------------------------------------------------
 void
 cmComputeTargetDepends::GetTargetDirectDepends(cmGeneratorTarget const* t,
                                                cmTargetDependSet& deps)
@@ -167,7 +163,6 @@ cmComputeTargetDepends::GetTargetDirectDepends(cmGeneratorTarget const* t,
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeTargetDepends::CollectTargets()
 {
   // Collect all targets from all generators.
@@ -188,7 +183,6 @@ void cmComputeTargetDepends::CollectTargets()
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeTargetDepends::CollectDepends()
 {
   // Allocate the dependency graph adjacency lists.
@@ -201,7 +195,6 @@ void cmComputeTargetDepends::CollectDepends()
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
 {
   // Get the depender.
@@ -287,7 +280,6 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
   }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
                                              const cmGeneratorTarget* dependee,
                                              const std::string& config,
@@ -312,7 +304,6 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
                                              cmLinkItem const& dependee_name,
                                              std::set<std::string> &emitted)
@@ -344,7 +335,6 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddTargetDepend(
   int depender_index, cmLinkItem const& dependee_name,
   bool linking)
@@ -411,7 +401,6 @@ void cmComputeTargetDepends::AddTargetDepend(
     }
 }
 
-//----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddTargetDepend(int depender_index,
                                              const cmGeneratorTarget* dependee,
                                              bool linking)
@@ -446,7 +435,6 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
     }
 }
 
-//----------------------------------------------------------------------------
 void
 cmComputeTargetDepends::DisplayGraph(Graph const& graph,
                                      const std::string& name)
@@ -470,7 +458,6 @@ cmComputeTargetDepends::DisplayGraph(Graph const& graph,
   fprintf(stderr, "\n");
 }
 
-//----------------------------------------------------------------------------
 void
 cmComputeTargetDepends
 ::DisplayComponents(cmComputeComponentGraph const& ccg)
@@ -492,7 +479,6 @@ ::DisplayComponents(cmComputeComponentGraph const& ccg)
   fprintf(stderr, "\n");
 }
 
-//----------------------------------------------------------------------------
 bool
 cmComputeTargetDepends
 ::CheckComponents(cmComputeComponentGraph const& ccg)
@@ -532,7 +518,6 @@ ::CheckComponents(cmComputeComponentGraph const& ccg)
   return true;
 }
 
-//----------------------------------------------------------------------------
 void
 cmComputeTargetDepends
 ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c,
@@ -589,7 +574,6 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c,
   cmSystemTools::Error(e.str().c_str());
 }
 
-//----------------------------------------------------------------------------
 bool
 cmComputeTargetDepends
 ::IntraComponent(std::vector<int> const& cmap, int c, int i, int* head,
@@ -631,7 +615,6 @@ ::IntraComponent(std::vector<int> const& cmap, int c, int i, int* head,
   return true;
 }
 
-//----------------------------------------------------------------------------
 bool
 cmComputeTargetDepends
 ::ComputeFinalDepends(cmComputeComponentGraph const& ccg)