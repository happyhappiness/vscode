@@ -2008,10 +2008,60 @@ void cmake::GenerateGraphViz(const char* fileName)
     {
     return;
     }
-  str << "digraph G {" << std::endl;
-  str << "node [" << std::endl;
-  str << "  fontsize = \"12\"" << std::endl;
-  str << "];" << std::endl;
+  cmake cm;
+  cmGlobalGenerator ggi;
+  ggi.SetCMakeInstance(&cm);
+  std::auto_ptr<cmLocalGenerator> lg(ggi.CreateLocalGenerator());
+  lg->SetGlobalGenerator(&ggi);
+  cmMakefile *mf = lg->GetMakefile();
+
+  std::string infile = this->GetHomeOutputDirectory();
+  infile += "/CMakeGraphVizOptions.cmake";
+  if ( !cmSystemTools::FileExists(infile.c_str()) )
+    {
+    infile = this->GetHomeDirectory();
+    infile += "/CMakeGraphVizOptions.cmake";
+    if ( !cmSystemTools::FileExists(infile.c_str()) )
+      {
+      infile = "";
+      }
+    }
+
+  if ( !infile.empty() )
+    {
+    if ( !mf->ReadListFile(0, infile.c_str()) )
+      {
+      cmSystemTools::Error("Problem opening GraphViz options file: ", infile.c_str());
+      return;
+      }
+    std::cout << "Read GraphViz options file: " << infile.c_str() << std::endl;
+    }
+
+#define __set_if_not_set(var, value, cmakeDefinition) \
+  const char* var = mf->GetDefinition(cmakeDefinition); \
+  if ( !var ) \
+    { \
+    var = value; \
+    }
+  __set_if_not_set(graphType, "digraph", "GRAPHVIZ_GRAPH_TYPE");
+  __set_if_not_set(graphName, "GG", "GRAPHVIZ_GRAPH_NAME");
+  __set_if_not_set(graphHeader, "node [\n  fontsize = \"12\"\n];", "GRAPHVIZ_GRAPH_HEADER");
+  __set_if_not_set(graphNodePrefix, "node", "GRAPHVIZ_NODE_PREFIX");
+  const char* ignoreTargets = mf->GetDefinition("GRAPHVIZ_IGNORE_TARGETS");
+  std::set<cmStdString> ignoreTargetsSet;
+  if ( ignoreTargets )
+    {
+    std::vector<std::string> ignoreTargetsVector;
+    cmSystemTools::ExpandListArgument(ignoreTargets,ignoreTargetsVector);
+    std::vector<std::string>::iterator itvIt;
+    for ( itvIt = ignoreTargetsVector.begin(); itvIt != ignoreTargetsVector.end(); ++ itvIt )
+      {
+      ignoreTargetsSet.insert(itvIt->c_str());
+      }
+    }
+ 
+  str << graphType << " " << graphName << " {" << std::endl;
+  str << graphHeader << std::endl;
 
   cmGlobalGenerator* gg = this->GetGlobalGenerator();
   std::vector<cmLocalGenerator*> localGenerators;
@@ -2033,10 +2083,16 @@ void cmake::GenerateGraphViz(const char* fileName)
     cmTargets::iterator tit;
     for ( tit = targets->begin(); tit != targets->end(); ++ tit )
       {
+      const char* realTargetName = tit->first.c_str();
+      if ( ignoreTargetsSet.find(realTargetName) != ignoreTargetsSet.end() )
+        {
+        // Skip ignored targets
+        continue;
+        }
       //std::cout << "Found target: " << tit->first.c_str() << std::endl;
-      sprintf(tgtName, "node%d", cnt++);
-      targetNamesNodes[tit->first.c_str()] = tgtName;
-      targetPtrs[tit->first.c_str()] = &tit->second;
+      sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
+      targetNamesNodes[realTargetName] = tgtName;
+      targetPtrs[realTargetName] = &tit->second;
       //str << "    \"" << tgtName << "\" [ label=\"" << tit->first.c_str() <<  "\" shape=\"box\"];" << std::endl;
       }
     }
@@ -2049,17 +2105,28 @@ void cmake::GenerateGraphViz(const char* fileName)
       {
       const cmTarget::LinkLibraries* ll = &(tit->second.GetOriginalLinkLibraries());
       cmTarget::LinkLibraries::const_iterator llit;
+      const char* realTargetName = tit->first.c_str();
+      if ( ignoreTargetsSet.find(realTargetName) != ignoreTargetsSet.end() )
+        {
+        // Skip ignored targets
+        continue;
+        }
       if ( ll->size() > 0 )
         {
-        targetDeps[tit->first.c_str()] = 1;
+        targetDeps[realTargetName] = 1;
         }
       for ( llit = ll->begin(); llit != ll->end(); ++ llit )
         {
         const char* libName = llit->first.c_str();
         std::map<cmStdString, cmStdString>::iterator tarIt = targetNamesNodes.find(libName);
+        if ( ignoreTargetsSet.find(libName) != ignoreTargetsSet.end() )
+          {
+          // Skip ignored targets
+          continue;
+          }
         if ( tarIt == targetNamesNodes.end() )
           {
-          sprintf(tgtName, "node%d", cnt++);
+          sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
           targetDeps[libName] = 2;
           targetNamesNodes[libName] = tgtName;
           //str << "    \"" << tgtName << "\" [ label=\"" << libName <<  "\" shape=\"ellipse\"];" << std::endl;
@@ -2085,7 +2152,7 @@ void cmake::GenerateGraphViz(const char* fileName)
     if ( tarIt == targetNamesNodes.end() )
       {
       // We should not be here.
-      std::cout << "Cannot find library: " << newTargetName << " even though it was added in the previous pass" << std::endl;
+      std::cout << __LINE__ << " Cannot find library: " << newTargetName << " even though it was added in the previous pass" << std::endl;
       abort();
       }
 
@@ -2096,7 +2163,7 @@ void cmake::GenerateGraphViz(const char* fileName)
       if ( tarTypeIt == targetPtrs.end() )
         {
         // We should not be here.
-        std::cout << "Cannot find library: " << newTargetName << " even though it was added in the previous pass" << std::endl;
+        std::cout << __LINE__ << " Cannot find library: " << newTargetName << " even though it was added in the previous pass" << std::endl;
         abort();
         }
       cmTarget* tg = tarTypeIt->second;
@@ -2147,7 +2214,7 @@ void cmake::GenerateGraphViz(const char* fileName)
         if ( tarIt == targetNamesNodes.end() )
           {
           // We should not be here.
-          std::cout << "Cannot find library: " << libName << " even though it was added in the previous pass" << std::endl;
+          std::cout << __LINE__ << " Cannot find library: " << libName << " even though it was added in the previous pass" << std::endl;
           abort();
           }
         str << "    \"" << cmakeTarIt->second.c_str() << "\" -> \"" << tarIt->second.c_str() << "\"" << std::endl;