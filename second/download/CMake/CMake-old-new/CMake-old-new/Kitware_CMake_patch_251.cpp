@@ -11,7 +11,7 @@
 ============================================================================*/
 #include "cmCoreTryCompile.h"
 #include "cmake.h"
-#include "cmLocalGenerator.h"
+#include "cmOutputConverter.h"
 #include "cmGlobalGenerator.h"
 #include "cmAlgorithms.h"
 #include "cmExportTryCompileFileGenerator.h"
@@ -322,7 +322,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       std::string langFlags = "CMAKE_" + *li + "_FLAGS";
       const char* flags = this->Makefile->GetDefinition(langFlags);
       fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
-              cmLocalGenerator::EscapeForCMake(flags?flags:"").c_str());
+              cmOutputConverter::EscapeForCMake(flags?flags:"").c_str());
       fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
               " ${COMPILE_DEFINITIONS}\")\n", li->c_str(), li->c_str());
       }
@@ -355,7 +355,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
         const char* exeLinkFlags =
           this->Makefile->GetDefinition("CMAKE_EXE_LINKER_FLAGS");
         fprintf(fout, "set(CMAKE_EXE_LINKER_FLAGS %s)\n",
-                cmLocalGenerator::EscapeForCMake(
+                cmOutputConverter::EscapeForCMake(
                     exeLinkFlags ? exeLinkFlags : "").c_str());
         } break;
       }