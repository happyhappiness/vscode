@@ -308,7 +308,7 @@ void cmGlobalGenerator::FindMakeProgram(cmMakefile* mf)
     makeProgram += "/";
     makeProgram += saveFile;
     mf->AddCacheDefinition("CMAKE_MAKE_PROGRAM", makeProgram.c_str(),
-                           "make program", cmState::FILEPATH);
+                           "make program", cmStateEnums::FILEPATH);
   }
 }
 
@@ -1103,7 +1103,7 @@ void cmGlobalGenerator::Configure()
   sprintf(num, "%d", static_cast<int>(this->Makefiles.size()));
   this->GetCMakeInstance()->AddCacheEntry("CMAKE_NUMBER_OF_MAKEFILES", num,
                                           "number of local generators",
-                                          cmState::INTERNAL);
+                                          cmStateEnums::INTERNAL);
 
   // check for link libraries and include directories containing "NOTFOUND"
   // and for infinite loops
@@ -1886,8 +1886,8 @@ void cmGlobalGenerator::EnableLanguagesFromGenerator(cmGlobalGenerator* gen,
   this->TryCompileOuterMakefile = mf;
   const char* make =
     gen->GetCMakeInstance()->GetCacheDefinition("CMAKE_MAKE_PROGRAM");
-  this->GetCMakeInstance()->AddCacheEntry("CMAKE_MAKE_PROGRAM", make,
-                                          "make program", cmState::FILEPATH);
+  this->GetCMakeInstance()->AddCacheEntry(
+    "CMAKE_MAKE_PROGRAM", make, "make program", cmStateEnums::FILEPATH);
   // copy the enabled languages
   this->GetCMakeInstance()->GetState()->SetEnabledLanguages(
     gen->GetCMakeInstance()->GetState()->GetEnabledLanguages());