@@ -242,8 +242,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       }
 
     // Detect languages to enable.
-    cmLocalGenerator* lg = this->Makefile->GetLocalGenerator();
-    cmGlobalGenerator* gg = lg->GetGlobalGenerator();
+    cmGlobalGenerator* gg = this->Makefile->GetGlobalGenerator();
     std::set<std::string> testLangs;
     for(std::vector<std::string>::iterator si = sources.begin();
         si != sources.end(); ++si)
@@ -323,7 +322,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       std::string langFlags = "CMAKE_" + *li + "_FLAGS";
       const char* flags = this->Makefile->GetDefinition(langFlags);
       fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
-              lg->EscapeForCMake(flags?flags:"").c_str());
+              cmLocalGenerator::EscapeForCMake(flags?flags:"").c_str());
       fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
               " ${COMPILE_DEFINITIONS}\")\n", li->c_str(), li->c_str());
       }
@@ -356,7 +355,8 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
         const char* exeLinkFlags =
           this->Makefile->GetDefinition("CMAKE_EXE_LINKER_FLAGS");
         fprintf(fout, "set(CMAKE_EXE_LINKER_FLAGS %s)\n",
-                lg->EscapeForCMake(exeLinkFlags?exeLinkFlags:"").c_str());
+                cmLocalGenerator::EscapeForCMake(
+                    exeLinkFlags ? exeLinkFlags : "").c_str());
         } break;
       }
     fprintf(fout, "set(CMAKE_EXE_LINKER_FLAGS \"${CMAKE_EXE_LINKER_FLAGS}"