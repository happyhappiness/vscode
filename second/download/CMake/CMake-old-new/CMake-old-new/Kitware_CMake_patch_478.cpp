@@ -482,6 +482,7 @@ void cmStringCommand::ClearMatches(cmMakefile* mf)
     char name[128];
     sprintf(name, "CMAKE_MATCH_%d", i);
     mf->AddDefinition(name, "");
+    mf->MarkVariableAsUsed(name);
     }
 }
 
@@ -493,6 +494,7 @@ void cmStringCommand::StoreMatches(cmMakefile* mf,cmsys::RegularExpression& re)
     char name[128];
     sprintf(name, "CMAKE_MATCH_%d", i);
     mf->AddDefinition(name, re.match(i).c_str());
+    mf->MarkVariableAsUsed(name);
     }
 }
 