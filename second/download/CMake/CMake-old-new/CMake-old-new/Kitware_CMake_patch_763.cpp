@@ -53,7 +53,6 @@ cmMakefile::cmMakefile()
   this->AddSourceGroup("", "^.*$");
   this->AddSourceGroup("Source Files", "\\.(cpp|C|c|cxx|rc|def|r|odl|idl|hpj|bat)$");
   this->AddSourceGroup("Header Files", "\\.(h|hh|hpp|hxx|hm|inl)$");
-  this->AddDefaultCommands();
   this->AddDefaultDefinitions();
 }
 
@@ -76,30 +75,6 @@ unsigned int cmMakefile::GetCacheMinorVersion()
 }
 
 
-void cmMakefile::AddDefaultCommands()
-{
-  std::list<cmCommand*> commands;
-  GetPredefinedCommands(commands);
-  for(std::list<cmCommand*>::iterator i = commands.begin();
-      i != commands.end(); ++i)
-    {
-    this->AddCommand(*i);
-    }
-#if defined(_WIN32) || defined(__CYGWIN__)
-  this->AddDefinition("WIN32", "1");
-#else
-  this->AddDefinition("UNIX", "1");
-#endif
-  // Cygwin is more like unix so enable the unix commands
-#if defined(__CYGWIN__)
-  this->AddDefinition("UNIX", "1");
-  this->AddDefinition("CYGWIN", "1");
-#endif
-#if defined(__APPLE__)
-  this->AddDefinition("APPLE", "1");
-#endif
-}
-
 cmMakefile::~cmMakefile()
 {
   for(std::vector<cmSourceFile*>::iterator i = m_SourceFiles.begin();
@@ -111,11 +86,6 @@ cmMakefile::~cmMakefile()
     {
     delete m_UsedCommands[i];
     }
-  for(RegisteredCommandsMap::iterator j = m_Commands.begin();
-      j != m_Commands.end(); ++j)
-    {
-    delete (*j).second;
-    }
   for(DataMap::const_iterator d = m_DataMap.begin();
       d != m_DataMap.end(); ++d)
     {
@@ -184,7 +154,7 @@ void cmMakefile::Print() const
 
 bool cmMakefile::CommandExists(const char* name) const
 {
-  return (m_Commands.find(name) != m_Commands.end());
+  return m_LocalGenerator->GetGlobalGenerator()->GetCMakeInstance()->CommandExists(name);
 }
       
 void cmMakefile::ExecuteCommand(std::string const &name,
@@ -196,10 +166,10 @@ void cmMakefile::ExecuteCommand(std::string const &name,
     return;
     }
   // execute the command
-  RegisteredCommandsMap::iterator pos = m_Commands.find(name);
-  if(pos != m_Commands.end())
+  cmCommand *rm = 
+    m_LocalGenerator->GetGlobalGenerator()->GetCMakeInstance()->GetCommand(name.c_str());
+  if(rm)
     {
-    cmCommand* rm = (*pos).second;
     cmCommand* usedCommand = rm->Clone();
     usedCommand->SetMakefile(this);
     bool keepCommand = false;
@@ -378,8 +348,7 @@ bool cmMakefile::ReadListFile(const char* filename, const char* external)
 
 void cmMakefile::AddCommand(cmCommand* wg)
 {
-  std::string name = wg->GetName();
-  m_Commands.insert( RegisteredCommandsMap::value_type(name, wg));
+  m_LocalGenerator->GetGlobalGenerator()->GetCMakeInstance()->AddCommand(wg);
 }
 
   // Set the make file 
@@ -898,32 +867,6 @@ const char* cmMakefile::GetDefinition(const char* name) const
   return this->GetCacheManager()->GetCacheValue(name);
 }
 
-int cmMakefile::DumpDocumentationToFile(std::ostream& f)
-{
-  // Open the supplied filename
-  
-  // Loop over all registered commands and print out documentation
-  const char *name;
-  const char *terse;
-  const char *full;
-  char tmp[1024];
-  sprintf(tmp,"Version %d.%d", cmMakefile::GetMajorVersion(),
-          cmMakefile::GetMinorVersion());
-  f << "<html>\n";
-  f << "<h1>Documentation for commands of CMake " << tmp << "</h1>\n";
-  f << "<ul>\n";
-  for(RegisteredCommandsMap::iterator j = m_Commands.begin();
-      j != m_Commands.end(); ++j)
-    {
-    name = (*j).second->GetName();
-    terse = (*j).second->GetTerseDocumentation();
-    full = (*j).second->GetFullDocumentation();
-    f << "<li><b>" << name << "</b> - " << terse << std::endl
-      << "<br><i>Usage:</i> " << full << "</li>" << std::endl << std::endl;
-    }
-  f << "</ul></html>\n";
-  return 1;
-}
 
 
 const char *cmMakefile::ExpandVariablesInString(std::string& source) const
@@ -1124,6 +1067,20 @@ void cmMakefile::RemoveVariablesInString(std::string& source,
  */
 void cmMakefile::AddDefaultDefinitions()
 {
+#if defined(_WIN32) || defined(__CYGWIN__)
+  this->AddDefinition("WIN32", "1");
+#else
+  this->AddDefinition("UNIX", "1");
+#endif
+  // Cygwin is more like unix so enable the unix commands
+#if defined(__CYGWIN__)
+  this->AddDefinition("UNIX", "1");
+  this->AddDefinition("CYGWIN", "1");
+#endif
+#if defined(__APPLE__)
+  this->AddDefinition("APPLE", "1");
+#endif
+
 #if defined(_WIN32) && !defined(__CYGWIN__)
   this->AddDefinition("CMAKE_CFG_INTDIR","$(IntDir)");
 #else
@@ -1373,7 +1330,7 @@ void cmMakefile::ExpandSourceListArguments(
 }
 
 int cmMakefile::TryCompile(const char *srcdir, const char *bindir, 
-                           const char *projectName)
+                           const char *projectName, const char *targetName)
 {
   if (!m_LocalGenerator)
     {
@@ -1433,17 +1390,13 @@ int cmMakefile::TryCompile(const char *srcdir, const char *bindir,
     }
 
   // finally call the generator to actually build the resulting project
-  gg->TryCompile(srcdir,bindir,projectName);
+  int ret = gg->TryCompile(srcdir,bindir,projectName, targetName);
 
   cmSystemTools::ChangeDirectory(cwd.c_str());
-  return 0;
+  return ret;
 }
 
 cmCacheManager *cmMakefile::GetCacheManager() const
 {
-  if (m_LocalGenerator)
-    {
-    return m_LocalGenerator->GetGlobalGenerator()->GetCMakeInstance()->GetCacheManager();
-    }
-  return 0;
+  return m_LocalGenerator->GetGlobalGenerator()->GetCMakeInstance()->GetCacheManager();
 }