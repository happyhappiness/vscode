@@ -285,7 +285,7 @@ cmComputeLinkDepends::AllocateLinkEntry(std::string const& item)
     lei = this->LinkEntryIndex.insert(index_entry).first;
   this->EntryList.push_back(LinkEntry());
   this->InferredDependSets.push_back(0);
-  this->EntryConstraintGraph.push_back(NodeList());
+  this->EntryConstraintGraph.push_back(EdgeList());
   return lei;
 }
 
@@ -669,7 +669,7 @@ void cmComputeLinkDepends::CleanConstraintGraph()
     cmsys_stl::sort(i->begin(), i->end());
 
     // Make the edge list unique.
-    NodeList::iterator last = cmsys_stl::unique(i->begin(), i->end());
+    EdgeList::iterator last = cmsys_stl::unique(i->begin(), i->end());
     i->erase(last, i->end());
     }
 }
@@ -681,9 +681,9 @@ void cmComputeLinkDepends::DisplayConstraintGraph()
   cmOStringStream e;
   for(unsigned int i=0; i < this->EntryConstraintGraph.size(); ++i)
     {
-    NodeList const& nl = this->EntryConstraintGraph[i];
+    EdgeList const& nl = this->EntryConstraintGraph[i];
     e << "item " << i << " is [" << this->EntryList[i].Item << "]\n";
-    for(NodeList::const_iterator j = nl.begin(); j != nl.end(); ++j)
+    for(EdgeList::const_iterator j = nl.begin(); j != nl.end(); ++j)
       {
       e << "  item " << *j << " must follow it\n";
       }
@@ -758,10 +758,11 @@ cmComputeLinkDepends::DisplayComponents()
       fprintf(stderr, "  item %d [%s]\n", i,
               this->EntryList[i].Item.c_str());
       }
-    NodeList const& ol = this->CCG->GetComponentGraphEdges(c);
-    for(NodeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
+    EdgeList const& ol = this->CCG->GetComponentGraphEdges(c);
+    for(EdgeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
       {
-      fprintf(stderr, "  followed by Component (%d)\n", *oi);
+      int i = *oi;
+      fprintf(stderr, "  followed by Component (%d)\n", i);
       }
     fprintf(stderr, "  topo order index %d\n",
             this->ComponentOrder[c]);
@@ -784,8 +785,8 @@ void cmComputeLinkDepends::VisitComponent(unsigned int c)
   // Visit the neighbors of the component first.
   // Run in reverse order so the topological order will preserve the
   // original order where there are no constraints.
-  NodeList const& nl = this->CCG->GetComponentGraphEdges(c);
-  for(NodeList::const_reverse_iterator ni = nl.rbegin();
+  EdgeList const& nl = this->CCG->GetComponentGraphEdges(c);
+  for(EdgeList::const_reverse_iterator ni = nl.rbegin();
       ni != nl.rend(); ++ni)
     {
     this->VisitComponent(*ni);
@@ -856,8 +857,8 @@ void cmComputeLinkDepends::VisitEntry(int index)
   // are now pending.
   if(completed)
     {
-    NodeList const& ol = this->CCG->GetComponentGraphEdges(component);
-    for(NodeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
+    EdgeList const& ol = this->CCG->GetComponentGraphEdges(component);
+    for(EdgeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
       {
       // This entire component is now pending no matter whether it has
       // been partially seen already.