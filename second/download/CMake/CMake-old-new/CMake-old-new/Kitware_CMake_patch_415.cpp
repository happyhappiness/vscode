@@ -534,8 +534,12 @@ void cmStringCommand::ClearMatches(cmMakefile* mf)
     {
     char name[128];
     sprintf(name, "CMAKE_MATCH_%d", i);
-    mf->AddDefinition(name, "");
-    mf->MarkVariableAsUsed(name);
+    const char* s = mf->GetDefinition(name);
+    if(s && *s != 0)
+      {
+      mf->AddDefinition(name, "");
+      mf->MarkVariableAsUsed(name);
+      }
     }
 }
 
@@ -544,10 +548,14 @@ void cmStringCommand::StoreMatches(cmMakefile* mf,cmsys::RegularExpression& re)
 {
   for (unsigned int i=0; i<10; i++)
     {
-    char name[128];
-    sprintf(name, "CMAKE_MATCH_%d", i);
-    mf->AddDefinition(name, re.match(i).c_str());
-    mf->MarkVariableAsUsed(name);
+    std::string m = re.match(i);
+    if(m.size() > 0)
+      {
+      char name[128];
+      sprintf(name, "CMAKE_MATCH_%d", i);
+      mf->AddDefinition(name, re.match(i).c_str());
+      mf->MarkVariableAsUsed(name);
+      }
     }
 }
 