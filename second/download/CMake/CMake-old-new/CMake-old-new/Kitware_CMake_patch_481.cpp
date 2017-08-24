@@ -150,8 +150,8 @@ cmComputeTargetDepends::GetTargetDirectDepends(cmTarget* t,
   int i = tii->second;
 
   // Get its final dependencies.
-  NodeList const& nl = this->FinalGraph[i];
-  for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+  EdgeList const& nl = this->FinalGraph[i];
+  for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
     {
     deps.insert(this->Targets[*ni]);
     }
@@ -283,11 +283,11 @@ cmComputeTargetDepends::DisplayGraph(Graph const& graph, const char* name)
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
@@ -383,8 +383,8 @@ ::ComplainAboutBadComponent(cmComputeComponentGraph const& ccg, int c)
       << cmTarget::TargetTypeNames[depender->GetType()] << "\n";
 
     // List its dependencies that are inside the component.
-    NodeList const& nl = this->InitialGraph[i];
-    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+    EdgeList const& nl = this->InitialGraph[i];
+    for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
       int j = *ni;
       if(cmap[j] == c)
@@ -425,8 +425,8 @@ ::ComputeFinalDepends(cmComputeComponentGraph const& ccg)
   for(int depender_component=0; depender_component < n; ++depender_component)
     {
     int depender_component_tail = components[depender_component].back();
-    NodeList const& nl = cgraph[depender_component];
-    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
+    EdgeList const& nl = cgraph[depender_component];
+    for(EdgeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
       {
       int dependee_component = *ni;
       int dependee_component_head = components[dependee_component].front();