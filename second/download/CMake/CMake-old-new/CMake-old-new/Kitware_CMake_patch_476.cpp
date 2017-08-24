@@ -164,7 +164,7 @@ void cmGraphVizWriter::WritePerTargetFiles(const char* fileName)
       return;
       }
 
-    fprintf(stderr, "Writing %s...\n", currentFilename.c_str());
+    std::cout << "Writing " << currentFilename << "..." << std::endl;
     this->WriteHeader(str);
 
     this->WriteConnections(ptrIt->first.c_str(),
@@ -184,7 +184,8 @@ void cmGraphVizWriter::WriteGlobalFile(const char* fileName)
     }
   this->WriteHeader(str);
 
-  fprintf(stderr, "Writing %s...\n", fileName);
+  std::cout << "Writing " << fileName << "..." << std::endl;
+
   std::set<std::string> insertedConnections;
   std::set<std::string> insertedNodes;
 