@@ -2835,10 +2835,31 @@ const char* cmake::GetCPackCommand()
     return this->CPackCommand.c_str();
 }
 
-// for target deps
-#define DOT_DEP_TARGET 1
-#define DOT_DEP_EXTERNAL 2
-#define DOT_DEP_NONE 0
+
+static const char* getShapeForTarget(const cmTarget* target)
+{
+  if (!target)
+    {
+    return "ellipse";
+    }
+
+  switch ( target->GetType() )
+    {
+    case cmTarget::EXECUTABLE:
+      return "house";
+    case cmTarget::STATIC_LIBRARY:
+      return "diamond";
+    case cmTarget::SHARED_LIBRARY:
+      return "polygon";
+    case cmTarget::MODULE_LIBRARY:
+      return "octagon";
+    default:
+      break;
+    }
+
+  return "box";
+}
+
 
 void cmake::GenerateGraphViz(const char* fileName) const
 {
@@ -2910,72 +2931,27 @@ void cmake::GenerateGraphViz(const char* fileName) const
   const std::vector<cmLocalGenerator*>& localGenerators =
       gg->GetLocalGenerators();
 
-  std::map<cmStdString, int> targetDeps;
   std::map<cmStdString, const cmTarget*> targetPtrs;
   std::map<cmStdString, cmStdString> targetNamesNodes; // maps from the actual strings to node names in dot
   int cnt = 0;
   cnt += getAllTargets(ignoreTargetsSet, targetNamesNodes, targetPtrs,
                        graphNodePrefix);
 
   cnt += getAllExternalLibs(ignoreTargetsSet, targetNamesNodes, targetPtrs,
-                            targetDeps, graphNodePrefix);
+                            graphNodePrefix);
 
 
   // Write out nodes
-  for(std::map<cmStdString, int>::const_iterator depIt = targetDeps.begin();
-      depIt != targetDeps.end();
-      ++ depIt )
+  for(std::map<cmStdString, const cmTarget*>::const_iterator tarIt =
+         targetPtrs.begin(); tarIt != targetPtrs.end(); ++ tarIt )
     {
-    const char* newTargetName = depIt->first.c_str();
-    std::map<cmStdString, cmStdString>::const_iterator tarIt =
+    const char* newTargetName = tarIt->first.c_str();
+    std::map<cmStdString, cmStdString>::const_iterator nameIt =
                                           targetNamesNodes.find(newTargetName);
-    if ( tarIt == targetNamesNodes.end() )
-      {
-      // We should not be here.
-      std::cout << __LINE__ << " Cannot find library: " << newTargetName
-                << " even though it was added in the previous pass"
-                << std::endl;
-      abort();
-      }
 
-    str << "    \"" << tarIt->second.c_str() << "\" [ label=\""
-        << newTargetName <<  "\" shape=\"";
-    if ( depIt->second == DOT_DEP_TARGET )
-      {
-      std::map<cmStdString, const cmTarget*>::const_iterator tarTypeIt =
-                                                targetPtrs.find(newTargetName);
-      if ( tarTypeIt == targetPtrs.end() )
-        {
-        // We should not be here.
-        std::cout << __LINE__ << " Cannot find library: " << newTargetName
-                  << " even though it was added in the previous pass"
-                  << std::endl;
-        abort();
-        }
-      const cmTarget* tg = tarTypeIt->second;
-      switch ( tg->GetType() )
-        {
-      case cmTarget::EXECUTABLE:
-        str << "house";
-        break;
-      case cmTarget::STATIC_LIBRARY:
-        str << "diamond";
-        break;
-      case cmTarget::SHARED_LIBRARY:
-        str << "polygon";
-        break;
-      case cmTarget::MODULE_LIBRARY:
-        str << "octagon";
-        break;
-      default:
-        str << "box";
-        }
-      }
-    else
-      {
-      str << "ellipse";
-      }
-    str << "\"];" << std::endl;
+    str << "    \"" << nameIt->second.c_str() << "\" [ label=\""
+        << newTargetName <<  "\" shape=\"" << getShapeForTarget(tarIt->second)
+        << "\"];" << std::endl;
     }
 
   // Now generate the connectivity
@@ -2989,13 +2965,13 @@ void cmake::GenerateGraphViz(const char* fileName) const
          tit != targets->end();
          ++ tit )
       {
-      std::map<cmStdString, int>::iterator dependIt
-                                         = targetDeps.find(tit->first.c_str());
-      if ( dependIt == targetDeps.end() )
+      std::map<cmStdString, const cmTarget* >::iterator cmakeTarIt
+                                         = targetPtrs.find(tit->first.c_str());
+      if ( cmakeTarIt == targetPtrs.end() ) // skip ignored targets
         {
         continue;
         }
-      std::map<cmStdString, cmStdString>::iterator cmakeTarIt =
+      std::map<cmStdString, cmStdString>::iterator targetNameIt =
                                      targetNamesNodes.find(tit->first.c_str());
       const cmTarget::LinkLibraryVectorType* ll =
                                      &(tit->second.GetOriginalLinkLibraries());
@@ -3005,17 +2981,17 @@ void cmake::GenerateGraphViz(const char* fileName) const
            ++ llit )
         {
         const char* libName = llit->first.c_str();
-        std::map<cmStdString, cmStdString>::const_iterator tarIt =
+        std::map<cmStdString, cmStdString>::const_iterator libNameIt =
                                                 targetNamesNodes.find(libName);
-        if ( tarIt == targetNamesNodes.end() )
+        if ( libNameIt == targetNamesNodes.end() )
           {
           // We should not be here.
           std::cout << __LINE__ << " Cannot find library: " << libName
             << " even though it was added in the previous pass" << std::endl;
           abort();
           }
-        str << "    \"" << cmakeTarIt->second.c_str() << "\" -> \""
-            << tarIt->second.c_str() << "\"" << std::endl;
+        str << "    \"" << targetNameIt->second.c_str() << "\" -> \""
+            << libNameIt->second.c_str() << "\"" << std::endl;
         }
       }
     }
@@ -3068,7 +3044,6 @@ int cmake::getAllTargets(const std::set<cmStdString>& ignoreTargetsSet,
 int cmake::getAllExternalLibs(const std::set<cmStdString>& ignoreTargetsSet,
                           std::map<cmStdString, cmStdString>& targetNamesNodes,
                           std::map<cmStdString, const cmTarget*>& targetPtrs,
-                          std::map<cmStdString, int>& targetDeps,
                           const char* graphNodePrefix) const
 {
   int cnt = 0;
@@ -3094,11 +3069,6 @@ int cmake::getAllExternalLibs(const std::set<cmStdString>& ignoreTargetsSet,
         }
       const cmTarget::LinkLibraryVectorType* ll =
                                      &(tit->second.GetOriginalLinkLibraries());
-      if ( ll->size() > 0 )
-        {
-        targetDeps[realTargetName] = DOT_DEP_TARGET;
-        fprintf(stderr, " + %s\n", realTargetName);
-        }
       for (cmTarget::LinkLibraryVectorType::const_iterator llit = ll->begin();
            llit != ll->end();
            ++ llit )
@@ -3110,26 +3080,17 @@ int cmake::getAllExternalLibs(const std::set<cmStdString>& ignoreTargetsSet,
           continue;
           }
 
-        std::map<cmStdString, cmStdString>::const_iterator tarIt =
-                                                targetNamesNodes.find(libName);
-        if ( tarIt == targetNamesNodes.end() )
+        std::map<cmStdString, const cmTarget*>::const_iterator tarIt =
+                                                      targetPtrs.find(libName);
+        if ( tarIt == targetPtrs.end() )
           {
           cmOStringStream ostr;
           ostr << graphNodePrefix << cnt++;
-          targetDeps[libName] = DOT_DEP_EXTERNAL;
           targetNamesNodes[libName] = ostr.str();
+          targetPtrs[libName] = NULL;
           //str << "    \"" << ostr.c_str() << "\" [ label=\"" << libName
           //<<  "\" shape=\"ellipse\"];" << std::endl;
           }
-        else
-          {
-          std::map<cmStdString, int>::const_iterator depIt =
-                                                      targetDeps.find(libName);
-          if ( depIt == targetDeps.end() )
-            {
-            targetDeps[libName] = DOT_DEP_TARGET;
-            }
-          }
         }
       }
     }