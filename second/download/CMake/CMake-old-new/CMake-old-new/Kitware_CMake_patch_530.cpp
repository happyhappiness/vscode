@@ -27,10 +27,10 @@ class cmLBDepend : public cmMakeDepend
 
 void cmLBDepend::DependWalk(cmDependInformation* info)
 {
-  std::ifstream fin(info->m_FullPath.c_str());
+  std::ifstream fin(info->FullPath.c_str());
   if(!fin)
     {
-    cmSystemTools::Error("error can not open ", info->m_FullPath.c_str());
+    cmSystemTools::Error("error can not open ", info->FullPath.c_str());
     return;
     }
   
@@ -66,14 +66,14 @@ void cmLBDepend::DependWalk(cmDependInformation* info)
       // extract the file being included
       std::string includeFile = currentline.substr(qstart+1, qend - qstart-1);
       // see if the include matches the regular expression
-      if(!m_IncludeFileRegularExpression.find(includeFile))
+      if(!this->IncludeFileRegularExpression.find(includeFile))
         {
-        if(m_Verbose)
+        if(this->Verbose)
           {
           std::string message = "Skipping ";
           message += includeFile;
           message += " for file ";
-          message += info->m_FullPath.c_str();
+          message += info->FullPath.c_str();
           cmSystemTools::Error(message.c_str(), 0);
           }
         continue;
@@ -95,8 +95,8 @@ void cmLBDepend::DependWalk(cmDependInformation* info)
           found = true;
           }
         for(std::vector<std::string>::iterator i = 
-              m_IncludeDirectories.begin();
-            i != m_IncludeDirectories.end(); ++i)
+              this->IncludeDirectories.begin();
+            i != this->IncludeDirectories.end(); ++i)
           {
           std::string path = *i;
           path = path + "/";
@@ -114,8 +114,8 @@ void cmLBDepend::DependWalk(cmDependInformation* info)
             found = true;
             }
           for(std::vector<std::string>::iterator i = 
-                m_IncludeDirectories.begin();
-              i != m_IncludeDirectories.end(); ++i)
+                this->IncludeDirectories.begin();
+              i != this->IncludeDirectories.end(); ++i)
             {
             std::string path = *i;
             path = path + "/";
@@ -134,8 +134,8 @@ void cmLBDepend::DependWalk(cmDependInformation* info)
             found = true;
             }
           for(std::vector<std::string>::iterator i = 
-                m_IncludeDirectories.begin();
-              i != m_IncludeDirectories.end(); ++i)
+                this->IncludeDirectories.begin();
+              i != this->IncludeDirectories.end(); ++i)
             {
             std::string path = *i;
             path = path + "/";
@@ -154,8 +154,8 @@ void cmLBDepend::DependWalk(cmDependInformation* info)
             found = true;
             }
           for(std::vector<std::string>::iterator i = 
-                m_IncludeDirectories.begin();
-              i != m_IncludeDirectories.end(); ++i)
+                this->IncludeDirectories.begin();
+              i != this->IncludeDirectories.end(); ++i)
             {
             std::string path = *i;
             path = path + "/";
@@ -185,8 +185,8 @@ bool cmOutputRequiredFilesCommand::InitialPass(std::vector<std::string> const& a
     }
 
   // store the arg for final pass
-  m_File = args[0];
-  m_OutputFile = args[1];
+  this->File = args[0];
+  this->OutputFile = args[1];
   
   return true;
 }
@@ -199,20 +199,20 @@ ListDependencies(cmDependInformation const *info,
   // add info to the visited set
   visited->insert(info);
   // now recurse with info's dependencies
-  for(cmDependInformation::DependencySet::const_iterator d = 
-        info->m_DependencySet.begin();
-      d != info->m_DependencySet.end(); ++d)
+  for(cmDependInformation::DependencySetType::const_iterator d = 
+        info->DependencySet.begin();
+      d != info->DependencySet.end(); ++d)
     {
     if (visited->find(*d) == visited->end())
       {
-      if(info->m_FullPath != "")
+      if(info->FullPath != "")
         {
-        std::string tmp = (*d)->m_FullPath;
+        std::string tmp = (*d)->FullPath;
         std::string::size_type pos = tmp.rfind('.');
         if(pos != std::string::npos && (tmp.substr(pos) != ".h"))
           {
           tmp = tmp.substr(0, pos);
-          fprintf(fout,"%s\n",(*d)->m_FullPath.c_str());
+          fprintf(fout,"%s\n",(*d)->FullPath.c_str());
           }
         }
       this->ListDependencies(*d,fout,visited);
@@ -223,22 +223,22 @@ ListDependencies(cmDependInformation const *info,
 void cmOutputRequiredFilesCommand::FinalPass()
 {
   
-  cmTargets &tgts = m_Makefile->GetTargets();
+  cmTargets &tgts = this->Makefile->GetTargets();
   for (cmTargets::iterator l = tgts.begin(); l != tgts.end(); l++)
     {
-    l->second.GenerateSourceFilesFromSourceLists(*m_Makefile);
+    l->second.GenerateSourceFilesFromSourceLists(*this->Makefile);
     }
 
   // compute the list of files
   cmLBDepend md;
-  md.SetMakefile(m_Makefile);
-  md.AddSearchPath(m_Makefile->GetStartDirectory());
+  md.SetMakefile(this->Makefile);
+  md.AddSearchPath(this->Makefile->GetStartDirectory());
   // find the depends for a file
-  const cmDependInformation *info = md.FindDependencies(m_File.c_str());
+  const cmDependInformation *info = md.FindDependencies(this->File.c_str());
   if (info)
     {
     // write them out
-    FILE *fout = fopen(m_OutputFile.c_str(),"w");
+    FILE *fout = fopen(this->OutputFile.c_str(),"w");
     std::set<cmDependInformation const*> visited;
     this->ListDependencies(info,fout, &visited);
     fclose(fout);