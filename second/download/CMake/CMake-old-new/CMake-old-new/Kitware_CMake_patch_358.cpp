@@ -186,7 +186,7 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
 //
 extern std::string GetVS6TargetName(const std::string& targetName);
 
-void cmLocalVisualStudio6Generator::CreateSingleDSP(const char *lname,
+void cmLocalVisualStudio6Generator::CreateSingleDSP(const std::string& lname,
                                                     cmTarget &target)
 {
   // add to the list of projects
@@ -263,7 +263,7 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmTarget& tgt)
 
 
 void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
-                                                 const char *libName,
+                                                 const std::string& libName,
                                                  cmTarget &target)
 {
   // For utility targets need custom command since pre- and post-
@@ -372,7 +372,7 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
 
 void cmLocalVisualStudio6Generator
 ::WriteGroup(const cmSourceGroup *sg, cmTarget& target,
-             std::ostream &fout, const char *libName)
+             std::ostream &fout, const std::string& libName)
 {
   cmGeneratorTarget* gt =
     this->GlobalGenerator->GetGeneratorTarget(&target);
@@ -572,9 +572,9 @@ ::AddUtilityCommandHack(cmTarget& target, int count,
 {
   // Create a fake output that forces the rule to run.
   char* output = new char[(strlen(this->Makefile->GetStartOutputDirectory()) +
-                           strlen(target.GetName()) + 30)];
+                           target.GetName().size() + 30)];
   sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),
-          target.GetName(), count);
+          target.GetName().c_str(), count);
   std::string comment = this->ConstructComment(origCommand, "<hack>");
 
   // Add the rule with the given dependencies and commands.
@@ -699,7 +699,7 @@ void cmLocalVisualStudio6Generator::WriteDSPEndGroup(std::ostream& fout)
 
 
 void cmLocalVisualStudio6Generator::SetBuildType(BuildType b,
-                                                 const char* libName,
+                                                 const std::string& libName,
                                                  cmTarget& target)
 {
   std::string root= this->Makefile->GetRequiredDefinition("CMAKE_ROOT");
@@ -813,8 +813,8 @@ cmLocalVisualStudio6Generator::MaybeCreateOutputDir(cmTarget& target,
 // look for custom rules on a target and collect them together
 std::string
 cmLocalVisualStudio6Generator::CreateTargetRules(cmTarget &target,
-                                                 const char* configName,
-                                                 const char * /* libName */)
+                                              const char* configName,
+                                              const std::string& /* libName */)
 {
   if (target.GetType() >= cmTarget::UTILITY )
     {
@@ -926,7 +926,7 @@ cmLocalVisualStudio6Generator::GetTargetIncludeOptions(cmTarget &target,
 
 void cmLocalVisualStudio6Generator
 ::WriteDSPHeader(std::ostream& fout,
-                 const char *libName, cmTarget &target,
+                 const std::string& libName, cmTarget &target,
                  std::vector<cmSourceGroup> &)
 {
   bool targetBuilds = (target.GetType() >= cmTarget::EXECUTABLE &&
@@ -1257,7 +1257,7 @@ ::WriteDSPHeader(std::ostream& fout,
       {
       cmSystemTools::Error
         ("CMake can not determine linker language for target: ",
-         target.GetName());
+         target.GetName().c_str());
       return;
       }
 
@@ -1679,7 +1679,7 @@ ::WriteDSPHeader(std::ostream& fout,
         {
         cmSystemTools::Error
           ("CMake can not determine linker language for target: ",
-           target.GetName());
+           target.GetName().c_str());
         return;
         }
       // if CXX is on and the target contains cxx code then add the cxx flags