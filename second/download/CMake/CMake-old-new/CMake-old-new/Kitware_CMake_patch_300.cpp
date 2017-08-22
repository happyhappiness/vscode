@@ -298,7 +298,7 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
 
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
-                                             const char* dependee_name,
+                                             const std::string& dependee_name,
                                              bool linking,
                                              std::set<cmStdString> &emitted)
 {
@@ -333,7 +333,7 @@ void cmComputeTargetDepends::AddInterfaceDepends(int depender_index,
 
 //----------------------------------------------------------------------------
 void cmComputeTargetDepends::AddTargetDepend(int depender_index,
-                                             const char* dependee_name,
+                                             const std::string& dependee_name,
                                              bool linking)
 {
   // Get the depender.
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