@@ -27,6 +27,7 @@ class cmLBDepend : public cmMakeDepend
 
 void cmLBDepend::DependWalk(cmDependInformation* info)
 {
+  m_Verbose = true;
   std::ifstream fin(info->m_FullPath.c_str());
   if(!fin)
     {
@@ -146,6 +147,26 @@ void cmLBDepend::DependWalk(cmDependInformation* info)
               }
             }
           }
+        if (!found)
+          {
+          cxxFile = root + ".txx";
+          if(cmSystemTools::FileExists(cxxFile.c_str()))
+            {
+            found = true;
+            }
+          for(std::vector<std::string>::iterator i = 
+                m_IncludeDirectories.begin();
+              i != m_IncludeDirectories.end(); ++i)
+            {
+            std::string path = *i;
+            path = path + "/";
+            path = path + cxxFile;
+            if(cmSystemTools::FileExists(path.c_str()))
+              {
+              found = true;
+              }
+            }
+          }
         if (found)
           {
           this->AddDependency(info, cxxFile.c_str());
@@ -178,7 +199,6 @@ ListDependencies(cmDependInformation const *info,
 {
   // add info to the visited set
   visited->insert(info);
-  
   // now recurse with info's dependencies
   for(cmDependInformation::DependencySet::const_iterator d = 
         info->m_DependencySet.begin();
@@ -190,7 +210,7 @@ ListDependencies(cmDependInformation const *info,
         {
         std::string tmp = (*d)->m_FullPath;
         std::string::size_type pos = tmp.rfind('.');
-        if(pos != std::string::npos && tmp.substr(pos) == ".cxx")
+        if(pos != std::string::npos && (tmp.substr(pos) != ".h"))
           {
           tmp = tmp.substr(0, pos);
           fprintf(fout,"%s\n",(*d)->m_FullPath.c_str());
@@ -213,7 +233,7 @@ void cmOutputRequiredFilesCommand::FinalPass()
   // compute the list of files
   cmLBDepend md;
   md.SetMakefile(m_Makefile);
-
+  md.AddSearchPath(m_Makefile->GetStartDirectory());
   // find the depends for a file
   const cmDependInformation *info = md.FindDependencies(m_File.c_str());
   if (info)