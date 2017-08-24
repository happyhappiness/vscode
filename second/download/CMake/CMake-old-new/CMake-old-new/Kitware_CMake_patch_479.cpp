@@ -195,15 +195,13 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
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
@@ -213,9 +211,14 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
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
@@ -225,6 +228,7 @@ void cmComputeTargetDepends::CollectTargetDepends(int depender_index)
       this->AddTargetDepend(depender_index, util->c_str(), false);
       }
     }
+  }
 }
 
 //----------------------------------------------------------------------------
@@ -272,7 +276,8 @@ void cmComputeTargetDepends::AddTargetDepend(int depender_index,
   int dependee_index = tii->second;
 
   // Add this entry to the dependency graph.
-  this->InitialGraph[depender_index].push_back(dependee_index);
+  this->InitialGraph[depender_index].push_back(
+    cmGraphEdge(dependee_index, !linking));
 }
 
 //----------------------------------------------------------------------------
@@ -291,8 +296,8 @@ cmComputeTargetDepends::DisplayGraph(Graph const& graph, const char* name)
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
@@ -390,7 +395,8 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c)
       if(cmap[j] == c)
         {
         cmTarget* dependee = this->Targets[j];
-        e << "    depends on \"" << dependee->GetName() << "\"\n";
+        e << "    depends on \"" << dependee->GetName() << "\""
+          << " (" << (ni->IsStrong()? "strong" : "weak") << ")\n";
         }
       }
     }