@@ -942,13 +942,13 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
       clock_finish = clock();
       time(&time_finish);
 
-      double clocks_per_sec = (double)CLOCKS_PER_SEC;
+      double clocks_per_sec = static_cast<double>(CLOCKS_PER_SEC);
       std::cout << "Elapsed time: "
-                << (long)(time_finish - time_start) << " s. (time)"
-                << ", "
-                << (double)(clock_finish - clock_start) / clocks_per_sec
-                << " s. (clock)"
-                << "\n";
+        << static_cast<long>(time_finish - time_start) << " s. (time)"
+        << ", "
+        << static_cast<double>(clock_finish - clock_start) / clocks_per_sec
+        << " s. (clock)"
+        << "\n";
       return 0;
     }
 
@@ -2368,7 +2368,6 @@ void cmake::GenerateGraphViz(const char* fileName)
   std::map<cmStdString, int> targetDeps;
   std::map<cmStdString, cmTarget*> targetPtrs;
   std::map<cmStdString, cmStdString> targetNamesNodes;
-  char tgtName[2048];
   int cnt = 0;
   // First pass get the list of all cmake targets
   for ( lit = localGenerators.begin(); lit != localGenerators.end(); ++ lit )
@@ -2384,8 +2383,9 @@ void cmake::GenerateGraphViz(const char* fileName)
         continue;
         }
       //std::cout << "Found target: " << tit->first.c_str() << std::endl;
-      sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
-      targetNamesNodes[realTargetName] = tgtName;
+      cmOStringStream ostr;
+      ostr << graphNodePrefix << cnt++;
+      targetNamesNodes[realTargetName] = ostr.str();
       targetPtrs[realTargetName] = &tit->second;
       }
     }
@@ -2421,10 +2421,11 @@ void cmake::GenerateGraphViz(const char* fileName)
           }
         if ( tarIt == targetNamesNodes.end() )
           {
-          sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
+          cmOStringStream ostr;
+          ostr << graphNodePrefix << cnt++;
           targetDeps[libName] = 2;
-          targetNamesNodes[libName] = tgtName;
-          //str << "    \"" << tgtName << "\" [ label=\"" << libName
+          targetNamesNodes[libName] = ostr.str();
+          //str << "    \"" << ostr.c_str() << "\" [ label=\"" << libName
           //<<  "\" shape=\"ellipse\"];" << std::endl;
           }
         else