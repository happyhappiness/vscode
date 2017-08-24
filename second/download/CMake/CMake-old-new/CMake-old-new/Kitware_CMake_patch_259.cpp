@@ -111,14 +111,14 @@ void cmLocalVisualStudio6Generator::Generate()
 void cmLocalVisualStudio6Generator::OutputDSPFile()
 {
   // If not an in source build, then create the output directory
-  if(strcmp(this->Makefile->GetCurrentBinaryDirectory(),
+  if(strcmp(this->GetCurrentBinaryDirectory(),
             this->GetSourceDirectory()) != 0)
     {
     if(!cmSystemTools::MakeDirectory
-       (this->Makefile->GetCurrentBinaryDirectory()))
+       (this->GetCurrentBinaryDirectory()))
       {
       cmSystemTools::Error("Error creating directory ",
-                           this->Makefile->GetCurrentBinaryDirectory());
+                           this->GetCurrentBinaryDirectory());
       }
     }
 
@@ -163,7 +163,7 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
       std::string::size_type pos = l->first.rfind('/');
       if(pos != std::string::npos)
         {
-        std::string dir = this->Makefile->GetCurrentBinaryDirectory();
+        std::string dir = this->GetCurrentBinaryDirectory();
         dir += "/";
         dir += l->first.substr(0, pos);
         if(!cmSystemTools::MakeDirectory(dir.c_str()))
@@ -189,7 +189,7 @@ void cmLocalVisualStudio6Generator::CreateSingleDSP(const std::string& lname,
 
   // create the dsp.cmake file
   std::string fname;
-  fname = this->Makefile->GetCurrentBinaryDirectory();
+  fname = this->GetCurrentBinaryDirectory();
   fname += "/";
   fname += pname;
   fname += ".dsp";
@@ -578,9 +578,9 @@ ::AddUtilityCommandHack(cmTarget& target, int count,
                         const cmCustomCommand& origCommand)
 {
   // Create a fake output that forces the rule to run.
-  char* output = new char[(strlen(this->Makefile->GetCurrentBinaryDirectory())
+  char* output = new char[(strlen(this->GetCurrentBinaryDirectory())
                            + target.GetName().size() + 30)];
-  sprintf(output,"%s/%s_force_%i", this->Makefile->GetCurrentBinaryDirectory(),
+  sprintf(output,"%s/%s_force_%i", this->GetCurrentBinaryDirectory(),
           target.GetName().c_str(), count);
   const char* comment = origCommand.GetComment();
   if(!comment && origCommand.GetOutputs().empty())
@@ -1964,7 +1964,7 @@ ::ComputeLongestObjectDirectory(cmTarget&) const
   // files directory for any configuration.  This is used to construct
   // object file names that do not produce paths that are too long.
   std::string dir_max;
-  dir_max += this->Makefile->GetCurrentBinaryDirectory();
+  dir_max += this->GetCurrentBinaryDirectory();
   dir_max += "/";
   dir_max += config_max;
   dir_max += "/";