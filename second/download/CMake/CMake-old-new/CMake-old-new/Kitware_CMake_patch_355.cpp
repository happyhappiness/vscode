@@ -254,7 +254,8 @@ cmComputeLinkDepends::Compute()
             "---------------------------------------"
             "---------------------------------------\n");
     fprintf(stderr, "Link dependency analysis for target %s, config %s\n",
-            this->Target->GetName(), this->Config?this->Config:"noconfig");
+            this->Target->GetName().c_str(),
+            this->Config?this->Config:"noconfig");
     this->DisplayConstraintGraph();
     }
 
@@ -620,7 +621,7 @@ cmComputeLinkDepends::AddLinkEntries(int depender_index,
 
 //----------------------------------------------------------------------------
 cmTarget const* cmComputeLinkDepends::FindTargetToLink(int depender_index,
-                                                 const char* name)
+                                                 const std::string& name)
 {
   // Look for a target in the scope of the depender.
   cmMakefile* mf = this->Makefile;
@@ -968,14 +969,14 @@ int cmComputeLinkDepends::ComputeComponentCount(NodeList const& nl)
 //----------------------------------------------------------------------------
 void cmComputeLinkDepends::DisplayFinalEntries()
 {
-  fprintf(stderr, "target [%s] links to:\n", this->Target->GetName());
+  fprintf(stderr, "target [%s] links to:\n", this->Target->GetName().c_str());
   for(std::vector<LinkEntry>::const_iterator lei =
         this->FinalLinkEntries.begin();
       lei != this->FinalLinkEntries.end(); ++lei)
     {
     if(lei->Target)
       {
-      fprintf(stderr, "  target [%s]\n", lei->Target->GetName());
+      fprintf(stderr, "  target [%s]\n", lei->Target->GetName().c_str());
       }
     else
       {