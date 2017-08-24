@@ -20,6 +20,28 @@
 
 #include <assert.h>
 
+static std::string const kCMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN =
+  "CMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN";
+static std::string const kCMAKE_C_COMPILER_TARGET = "CMAKE_C_COMPILER_TARGET";
+static std::string const kCMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN =
+  "CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN";
+static std::string const kCMAKE_CXX_COMPILER_TARGET =
+  "CMAKE_CXX_COMPILER_TARGET";
+static std::string const kCMAKE_ENABLE_EXPORTS = "CMAKE_ENABLE_EXPORTS";
+static std::string const kCMAKE_LINK_SEARCH_END_STATIC =
+  "CMAKE_LINK_SEARCH_END_STATIC";
+static std::string const kCMAKE_LINK_SEARCH_START_STATIC =
+  "CMAKE_LINK_SEARCH_START_STATIC";
+static std::string const kCMAKE_OSX_ARCHITECTURES = "CMAKE_OSX_ARCHITECTURES";
+static std::string const kCMAKE_OSX_DEPLOYMENT_TARGET =
+  "CMAKE_OSX_DEPLOYMENT_TARGET";
+static std::string const kCMAKE_OSX_SYSROOT = "CMAKE_OSX_SYSROOT";
+static std::string const kCMAKE_POSITION_INDEPENDENT_CODE =
+  "CMAKE_POSITION_INDEPENDENT_CODE";
+static std::string const kCMAKE_SYSROOT = "CMAKE_SYSROOT";
+static std::string const kCMAKE_TRY_COMPILE_OSX_ARCHITECTURES =
+  "CMAKE_TRY_COMPILE_OSX_ARCHITECTURES";
+
 int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv,
                                      bool isTryRun)
 {
@@ -383,76 +405,44 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv,
               fname.c_str());
     }
 
-    /* for the TRY_COMPILEs we want to be able to specify the architecture.
-      So the user can set CMAKE_OSX_ARCHITECTURES to i386;ppc and then set
-      CMAKE_TRY_COMPILE_OSX_ARCHITECTURES first to i386 and then to ppc to
-      have the tests run for each specific architecture. Since
-      cmLocalGenerator doesn't allow building for "the other"
-      architecture only via CMAKE_OSX_ARCHITECTURES.
-      */
-    if (this->Makefile->GetDefinition("CMAKE_TRY_COMPILE_OSX_ARCHITECTURES") !=
-        0) {
-      std::string flag = "-DCMAKE_OSX_ARCHITECTURES=";
-      flag += this->Makefile->GetSafeDefinition(
-        "CMAKE_TRY_COMPILE_OSX_ARCHITECTURES");
-      cmakeFlags.push_back(flag);
-    } else if (this->Makefile->GetDefinition("CMAKE_OSX_ARCHITECTURES") != 0) {
-      std::string flag = "-DCMAKE_OSX_ARCHITECTURES=";
-      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_ARCHITECTURES");
-      cmakeFlags.push_back(flag);
-    }
-    /* on APPLE also pass CMAKE_OSX_SYSROOT to the try_compile */
-    if (this->Makefile->GetDefinition("CMAKE_OSX_SYSROOT") != 0) {
-      std::string flag = "-DCMAKE_OSX_SYSROOT=";
-      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_SYSROOT");
-      cmakeFlags.push_back(flag);
-    }
-    /* on APPLE also pass CMAKE_OSX_DEPLOYMENT_TARGET to the try_compile */
-    if (this->Makefile->GetDefinition("CMAKE_OSX_DEPLOYMENT_TARGET") != 0) {
-      std::string flag = "-DCMAKE_OSX_DEPLOYMENT_TARGET=";
-      flag += this->Makefile->GetSafeDefinition("CMAKE_OSX_DEPLOYMENT_TARGET");
-      cmakeFlags.push_back(flag);
-    }
-    if (const char* cxxDef =
-          this->Makefile->GetDefinition("CMAKE_CXX_COMPILER_TARGET")) {
-      std::string flag = "-DCMAKE_CXX_COMPILER_TARGET=";
-      flag += cxxDef;
-      cmakeFlags.push_back(flag);
-    }
-    if (const char* cDef =
-          this->Makefile->GetDefinition("CMAKE_C_COMPILER_TARGET")) {
-      std::string flag = "-DCMAKE_C_COMPILER_TARGET=";
-      flag += cDef;
-      cmakeFlags.push_back(flag);
-    }
-    if (const char* tcxxDef = this->Makefile->GetDefinition(
-          "CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN")) {
-      std::string flag = "-DCMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN=";
-      flag += tcxxDef;
-      cmakeFlags.push_back(flag);
-    }
-    if (const char* tcDef = this->Makefile->GetDefinition(
-          "CMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN")) {
-      std::string flag = "-DCMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN=";
-      flag += tcDef;
-      cmakeFlags.push_back(flag);
-    }
-    if (const char* rootDef = this->Makefile->GetDefinition("CMAKE_SYSROOT")) {
-      std::string flag = "-DCMAKE_SYSROOT=";
-      flag += rootDef;
-      cmakeFlags.push_back(flag);
-    }
-    if (this->Makefile->GetDefinition("CMAKE_POSITION_INDEPENDENT_CODE") !=
-        0) {
-      fprintf(fout, "set(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
-    }
-    if (const char* lssDef =
-          this->Makefile->GetDefinition("CMAKE_LINK_SEARCH_START_STATIC")) {
-      fprintf(fout, "set(CMAKE_LINK_SEARCH_START_STATIC \"%s\")\n", lssDef);
-    }
-    if (const char* lssDef =
-          this->Makefile->GetDefinition("CMAKE_LINK_SEARCH_END_STATIC")) {
-      fprintf(fout, "set(CMAKE_LINK_SEARCH_END_STATIC \"%s\")\n", lssDef);
+    // Forward a set of variables to the inner project cache.
+    {
+      std::set<std::string> vars;
+      vars.insert(kCMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN);
+      vars.insert(kCMAKE_C_COMPILER_TARGET);
+      vars.insert(kCMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN);
+      vars.insert(kCMAKE_CXX_COMPILER_TARGET);
+      vars.insert(kCMAKE_ENABLE_EXPORTS);
+      vars.insert(kCMAKE_LINK_SEARCH_END_STATIC);
+      vars.insert(kCMAKE_LINK_SEARCH_START_STATIC);
+      vars.insert(kCMAKE_OSX_ARCHITECTURES);
+      vars.insert(kCMAKE_OSX_DEPLOYMENT_TARGET);
+      vars.insert(kCMAKE_OSX_SYSROOT);
+      vars.insert(kCMAKE_POSITION_INDEPENDENT_CODE);
+      vars.insert(kCMAKE_SYSROOT);
+
+      /* for the TRY_COMPILEs we want to be able to specify the architecture.
+         So the user can set CMAKE_OSX_ARCHITECTURES to i386;ppc and then set
+         CMAKE_TRY_COMPILE_OSX_ARCHITECTURES first to i386 and then to ppc to
+         have the tests run for each specific architecture. Since
+         cmLocalGenerator doesn't allow building for "the other"
+         architecture only via CMAKE_OSX_ARCHITECTURES.
+         */
+      if (const char* tcArchs = this->Makefile->GetDefinition(
+            kCMAKE_TRY_COMPILE_OSX_ARCHITECTURES)) {
+        vars.erase(kCMAKE_OSX_ARCHITECTURES);
+        std::string flag = "-DCMAKE_OSX_ARCHITECTURES=" + std::string(tcArchs);
+        cmakeFlags.push_back(flag);
+      }
+
+      for (std::set<std::string>::iterator vi = vars.begin(); vi != vars.end();
+           ++vi) {
+        std::string const& var = *vi;
+        if (const char* val = this->Makefile->GetDefinition(var)) {
+          std::string flag = "-D" + var + "=" + val;
+          cmakeFlags.push_back(flag);
+        }
+      }
     }
 
     /* Set the appropriate policy information for ENABLE_EXPORTS */
@@ -461,10 +451,6 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv,
                 cmPolicies::NEW
               ? "NEW"
               : "OLD");
-    if (const char* ee =
-          this->Makefile->GetDefinition("CMAKE_ENABLE_EXPORTS")) {
-      fprintf(fout, "set(CMAKE_ENABLE_EXPORTS %s)\n", ee);
-    }
 
     if (targetType == cmState::EXECUTABLE) {
       /* Put the executable at a known location (for COPY_FILE).  */