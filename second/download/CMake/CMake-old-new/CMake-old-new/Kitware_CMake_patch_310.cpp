@@ -311,7 +311,7 @@ void cmGlobalGenerator::FindMakeProgram(cmMakefile* mf)
     makeProgram += saveFile;
     mf->AddCacheDefinition("CMAKE_MAKE_PROGRAM", makeProgram.c_str(),
                            "make program",
-                           cmCacheManager::FILEPATH);
+                           cmState::FILEPATH);
     }
 }
 
@@ -1116,7 +1116,7 @@ void cmGlobalGenerator::Configure()
   sprintf(num,"%d",static_cast<int>(this->LocalGenerators.size()));
   this->GetCMakeInstance()->AddCacheEntry
     ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
-     "number of local generators", cmCacheManager::INTERNAL);
+     "number of local generators", cmState::INTERNAL);
 
   // check for link libraries and include directories containing "NOTFOUND"
   // and for infinite loops
@@ -1894,7 +1894,7 @@ void cmGlobalGenerator::EnableLanguagesFromGenerator(cmGlobalGenerator *gen,
     gen->GetCMakeInstance()->GetCacheDefinition("CMAKE_MAKE_PROGRAM");
   this->GetCMakeInstance()->AddCacheEntry("CMAKE_MAKE_PROGRAM", make,
                                           "make program",
-                                          cmCacheManager::FILEPATH);
+                                          cmState::FILEPATH);
   // copy the enabled languages
   this->LanguageEnabled = gen->LanguageEnabled;
   this->LanguagesReady = gen->LanguagesReady;