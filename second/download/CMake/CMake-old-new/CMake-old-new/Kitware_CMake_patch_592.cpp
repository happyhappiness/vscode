@@ -9,8 +9,8 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -34,7 +34,7 @@
 #include "windows.h"
 #endif
 
-#include <stdlib.h> 
+#include <stdlib.h>
 #include <math.h>
 #include <float.h>
 
@@ -63,22 +63,22 @@ class cmCTestUpdateHandlerSVNXMLParser : public cmXMLParser
 public:
   struct t_CommitLog
     {
-    int m_Revision;
-    std::string m_Author;
-    std::string m_Date;
-    std::string m_Message;
+    int Revision;
+    std::string Author;
+    std::string Date;
+    std::string Message;
     };
   cmCTestUpdateHandlerSVNXMLParser(cmCTestUpdateHandler* up)
-    : cmXMLParser(), m_UpdateHandler(up), m_MinRevision(-1), m_MaxRevision(-1)
+    : cmXMLParser(), UpdateHandler(up), MinRevision(-1), MaxRevision(-1)
     {
     }
 
   int Parse(const char* str)
     {
-    m_MinRevision = -1;
-    m_MaxRevision = -1;
+    this->MinRevision = -1;
+    this->MaxRevision = -1;
     int res = this->cmXMLParser::Parse(str);
-    if ( m_MinRevision == -1 || m_MaxRevision == -1 )
+    if ( this->MinRevision == -1 || this->MaxRevision == -1 )
       {
       return 0;
       }
@@ -87,63 +87,68 @@ class cmCTestUpdateHandlerSVNXMLParser : public cmXMLParser
 
   typedef std::vector<t_CommitLog> t_VectorOfCommits;
 
-  t_VectorOfCommits* GetCommits() { return &m_Commits; }
-  int GetMinRevision() { return m_MinRevision; }
-  int GetMaxRevision() { return m_MaxRevision; }
+  t_VectorOfCommits* GetCommits() { return &this->Commits; }
+  int GetMinRevision() { return this->MinRevision; }
+  int GetMaxRevision() { return this->MaxRevision; }
 
 protected:
   void StartElement(const char* name, const char** atts)
     {
     if ( strcmp(name, "logentry") == 0 )
       {
-      m_CommitLog = t_CommitLog();
+      this->CommitLog = t_CommitLog();
       const char* rev = this->FindAttribute(atts, "revision");
       if ( rev)
         {
-        m_CommitLog.m_Revision = atoi(rev);
-        if ( m_MinRevision < 0 || m_MinRevision > m_CommitLog.m_Revision )
+        this->CommitLog.Revision = atoi(rev);
+        if ( this->MinRevision < 0 ||
+          this->MinRevision > this->CommitLog.Revision )
           {
-          m_MinRevision = m_CommitLog.m_Revision;
+          this->MinRevision = this->CommitLog.Revision;
           }
-        if ( m_MaxRevision < 0 || m_MaxRevision < m_CommitLog.m_Revision )
+        if ( this->MaxRevision < 0 ||
+          this->MaxRevision < this->CommitLog.Revision )
           {
-          m_MaxRevision = m_CommitLog.m_Revision;
+          this->MaxRevision = this->CommitLog.Revision;
           }
         }
       }
-    m_CharacterData.erase(m_CharacterData.begin(), m_CharacterData.end());
+    this->CharacterData.erase(
+      this->CharacterData.begin(), this->CharacterData.end());
     }
   void EndElement(const char* name)
     {
     if ( strcmp(name, "logentry") == 0 )
       {
-      cmCTestLog(m_UpdateHandler->GetCTestInstance(), HANDLER_VERBOSE_OUTPUT,
-        "\tRevision: " << m_CommitLog.m_Revision<< std::endl
-        << "\tAuthor:   " << m_CommitLog.m_Author.c_str() << std::endl
-        << "\tDate:     " << m_CommitLog.m_Date.c_str() << std::endl
-        << "\tMessage:  " << m_CommitLog.m_Message.c_str() << std::endl);
-      m_Commits.push_back(m_CommitLog);
+      cmCTestLog(this->UpdateHandler->GetCTestInstance(),
+        HANDLER_VERBOSE_OUTPUT,
+        "\tRevision: " << this->CommitLog.Revision<< std::endl
+        << "\tAuthor:   " << this->CommitLog.Author.c_str() << std::endl
+        << "\tDate:     " << this->CommitLog.Date.c_str() << std::endl
+        << "\tMessage:  " << this->CommitLog.Message.c_str() << std::endl);
+      this->Commits.push_back(this->CommitLog);
       }
     else if ( strcmp(name, "author") == 0 )
       {
-      m_CommitLog.m_Author.assign(&(*(m_CharacterData.begin())),
-        m_CharacterData.size());
+      this->CommitLog.Author.assign(&(*(this->CharacterData.begin())),
+        this->CharacterData.size());
       }
     else if ( strcmp(name, "date") == 0 )
       {
-      m_CommitLog.m_Date.assign(&(*(m_CharacterData.begin())),
-        m_CharacterData.size());
+      this->CommitLog.Date.assign(&(*(this->CharacterData.begin())),
+        this->CharacterData.size());
       }
     else if ( strcmp(name, "msg") == 0 )
       {
-      m_CommitLog.m_Message.assign(&(*(m_CharacterData.begin())),
-        m_CharacterData.size());
+      this->CommitLog.Message.assign(&(*(this->CharacterData.begin())),
+        this->CharacterData.size());
       }
-    m_CharacterData.erase(m_CharacterData.begin(), m_CharacterData.end());
+    this->CharacterData.erase(this->CharacterData.begin(),
+      this->CharacterData.end());
     }
   void CharacterDataHandler(const char* data, int length)
     {
-    m_CharacterData.insert(m_CharacterData.end(), data, data+length);
+    this->CharacterData.insert(this->CharacterData.end(), data, data+length);
     }
   const char* FindAttribute( const char** atts, const char* attribute )
     {
@@ -164,13 +169,13 @@ class cmCTestUpdateHandlerSVNXMLParser : public cmXMLParser
     }
 
 private:
-  std::vector<char> m_CharacterData;
-  cmCTestUpdateHandler* m_UpdateHandler;
-  t_CommitLog m_CommitLog;
+  std::vector<char> CharacterData;
+  cmCTestUpdateHandler* UpdateHandler;
+  t_CommitLog CommitLog;
 
-  t_VectorOfCommits m_Commits;
-  int m_MinRevision;
-  int m_MaxRevision;
+  t_VectorOfCommits Commits;
+  int MinRevision;
+  int MaxRevision;
 };
 //**********************************************************************
 //----------------------------------------------------------------------
@@ -189,11 +194,11 @@ void cmCTestUpdateHandler::Initialize()
 //----------------------------------------------------------------------
 int cmCTestUpdateHandler::DetermineType(const char* cmd, const char* type)
 {
-  cmCTestLog(m_CTest, DEBUG, "Determine update type from command: " << cmd
+  cmCTestLog(this->CTest, DEBUG, "Determine update type from command: " << cmd
     << " and type: " << type << std::endl);
   if ( type && *type )
     {
-    cmCTestLog(m_CTest, DEBUG, "Type specified: " << type << std::endl);
+    cmCTestLog(this->CTest, DEBUG, "Type specified: " << type << std::endl);
     std::string stype = cmSystemTools::LowerCase(type);
     if ( stype.find("cvs") != std::string::npos )
       {
@@ -206,8 +211,8 @@ int cmCTestUpdateHandler::DetermineType(const char* cmd, const char* type)
     }
   else
     {
-    cmCTestLog(m_CTest, DEBUG, "Type not specified, check command: " << cmd
-      << std::endl);
+    cmCTestLog(this->CTest, DEBUG, "Type not specified, check command: "
+      << cmd << std::endl);
     std::string stype = cmSystemTools::LowerCase(cmd);
     if ( stype.find("cvs") != std::string::npos )
       {
@@ -219,8 +224,8 @@ int cmCTestUpdateHandler::DetermineType(const char* cmd, const char* type)
       }
     }
   std::string sourceDirectory = this->GetOption("SourceDirectory");
-  cmCTestLog(m_CTest, DEBUG, "Check directory: " << sourceDirectory.c_str()
-    << std::endl);
+  cmCTestLog(this->CTest, DEBUG, "Check directory: "
+    << sourceDirectory.c_str() << std::endl);
   sourceDirectory += "/.svn";
   if ( cmSystemTools::FileExists(sourceDirectory.c_str()) )
     {
@@ -254,50 +259,52 @@ int cmCTestUpdateHandler::ProcessHandler()
   const char* sourceDirectory = this->GetOption("SourceDirectory");
   if ( !sourceDirectory )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE,
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
       "Cannot find SourceDirectory  key in the DartConfiguration.tcl"
       << std::endl);
     return -1;
     }
 
   cmGeneratedFileStream ofs;
-  if ( !m_CTest->GetShowOnly() )
+  if ( !this->CTest->GetShowOnly() )
     {
     this->StartLogFile("Update", ofs);
     }
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "Updating the repository" << std::endl);
+  cmCTestLog(this->CTest, HANDLER_OUTPUT,
+    "Updating the repository" << std::endl);
 
   const char* initialCheckoutCommand = this->GetOption("InitialCheckout");
   if ( initialCheckoutCommand )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT,
+    cmCTestLog(this->CTest, HANDLER_OUTPUT,
       "   First perform the initil checkout: " << initialCheckoutCommand
       << std::endl);
     cmStdString parent = cmSystemTools::GetParentDirectory(sourceDirectory);
     if ( parent.empty() )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Something went wrong when trying "
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
+        "Something went wrong when trying "
         "to determine the parent directory of " << sourceDirectory
         << std::endl);
       return -1;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Perform checkout in directory: "
-      << parent.c_str() << std::endl);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT,
+      "   Perform checkout in directory: " << parent.c_str() << std::endl);
     if ( !cmSystemTools::MakeDirectory(parent.c_str()) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE,
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
         "Cannot create parent directory: " << parent.c_str()
         << " of the source directory: " << sourceDirectory << std::endl);
       return -1;
       }
     ofs << "* Run initial checkout" << std::endl;
     ofs << "  Command: " << initialCheckoutCommand << std::endl;
-    cmCTestLog(m_CTest, DEBUG, "   Before: "
+    cmCTestLog(this->CTest, DEBUG, "   Before: "
       << initialCheckoutCommand << std::endl);
-    bool retic = m_CTest->RunCommand(initialCheckoutCommand, &goutput,
+    bool retic = this->CTest->RunCommand(initialCheckoutCommand, &goutput,
       &errors, &retVal, parent.c_str(), 0 /* Timeout */);
-    cmCTestLog(m_CTest, DEBUG, "   After: "
+    cmCTestLog(this->CTest, DEBUG, "   After: "
       << initialCheckoutCommand << std::endl);
     ofs << "  Output: " << goutput.c_str() << std::endl;
     ofs << "  Errors: " << errors.c_str() << std::endl;
@@ -306,26 +313,27 @@ int cmCTestUpdateHandler::ProcessHandler()
       cmOStringStream ostr;
       ostr << "Problem running initial checkout Output [" << goutput
         << "] Errors [" << errors << "]";
-      cmCTestLog(m_CTest, ERROR_MESSAGE, ostr.str().c_str() << std::endl);
+      cmCTestLog(this->CTest, ERROR_MESSAGE, ostr.str().c_str() << std::endl);
       checkoutErrorMessages += ostr.str();
       updateProducedError = true;
       }
-    m_CTest->InitializeFromCommand(m_Command);
+    this->CTest->InitializeFromCommand(this->Command);
     }
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Updating the repository: "
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Updating the repository: "
     << sourceDirectory << std::endl);
 
   // Get update command
-  std::string updateCommand = m_CTest->GetCTestConfiguration("UpdateCommand");
+  std::string updateCommand
+    = this->CTest->GetCTestConfiguration("UpdateCommand");
   if ( updateCommand.empty() )
     {
-    updateCommand = m_CTest->GetCTestConfiguration("CVSCommand");
+    updateCommand = this->CTest->GetCTestConfiguration("CVSCommand");
     if ( updateCommand.empty() )
       {
-      updateCommand = m_CTest->GetCTestConfiguration("SVNCommand");
+      updateCommand = this->CTest->GetCTestConfiguration("SVNCommand");
       if ( updateCommand.empty() )
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE,
+        cmCTestLog(this->CTest, ERROR_MESSAGE,
           "Cannot find CVSCommand, SVNCommand, or UpdateCommand key in the "
           "DartConfiguration.tcl" << std::endl);
         return -1;
@@ -343,39 +351,40 @@ int cmCTestUpdateHandler::ProcessHandler()
   else
     {
     updateType = this->DetermineType(updateCommand.c_str(),
-      m_CTest->GetCTestConfiguration("UpdateType").c_str());
+      this->CTest->GetCTestConfiguration("UpdateType").c_str());
     }
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Use "
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Use "
     << cmCTestUpdateHandlerUpdateToString(updateType) << " repository type"
     << std::endl;);
 
   // And update options
-  std::string updateOptions = m_CTest->GetCTestConfiguration("UpdateOptions");
+  std::string updateOptions
+    = this->CTest->GetCTestConfiguration("UpdateOptions");
   if ( updateOptions.empty() )
     {
     switch (updateType)
       {
     case cmCTestUpdateHandler::e_CVS:
-      updateOptions = m_CTest->GetCTestConfiguration("CVSUpdateOptions");
+      updateOptions = this->CTest->GetCTestConfiguration("CVSUpdateOptions");
       if ( updateOptions.empty() )
         {
         updateOptions = "-dP";
         }
       break;
     case cmCTestUpdateHandler::e_SVN:
-      updateOptions = m_CTest->GetCTestConfiguration("SVNUpdateOptions");
+      updateOptions = this->CTest->GetCTestConfiguration("SVNUpdateOptions");
       break;
       }
     }
 
   // Get update time
   std::string extra_update_opts;
-  if ( m_CTest->GetTestModel() == cmCTest::NIGHTLY )
+  if ( this->CTest->GetTestModel() == cmCTest::NIGHTLY )
     {
-    struct tm* t = m_CTest->GetNightlyTime(
-      m_CTest->GetCTestConfiguration("NightlyStartTime"),
-      m_CTest->GetTomorrowTag());
+    struct tm* t = this->CTest->GetNightlyTime(
+      this->CTest->GetCTestConfiguration("NightlyStartTime"),
+      this->CTest->GetTomorrowTag());
     char current_time[1024];
     sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
       t->tm_year + 1900,
@@ -427,14 +436,14 @@ int cmCTestUpdateHandler::ProcessHandler()
   //
   if ( !command.empty() )
     {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
         "* Get repository information: " << command.c_str() << std::endl);
-    if ( !m_CTest->GetShowOnly() )
+    if ( !this->CTest->GetShowOnly() )
       {
       ofs << "* Get repository information" << std::endl;
       ofs << "  Command: " << command.c_str() << std::endl;
-      res = m_CTest->RunCommand(command.c_str(), &goutput, &errors,
-        &retVal, sourceDirectory, 0 /*m_TimeOut*/);
+      res = this->CTest->RunCommand(command.c_str(), &goutput, &errors,
+        &retVal, sourceDirectory, 0 /*this->TimeOut*/);
 
       ofs << "  Output: " << goutput.c_str() << std::endl;
       ofs << "  Errors: " << errors.c_str() << std::endl;
@@ -457,7 +466,7 @@ int cmCTestUpdateHandler::ProcessHandler()
             std::string currentRevisionString
               = current_revision_regex.match(1);
             svn_current_revision = atoi(currentRevisionString.c_str());
-            cmCTestLog(m_CTest, HANDLER_OUTPUT,
+            cmCTestLog(this->CTest, HANDLER_OUTPUT,
               "   Old revision of repository is: " << svn_current_revision
               << std::endl);
             }
@@ -467,26 +476,27 @@ int cmCTestUpdateHandler::ProcessHandler()
       }
     else
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
         "Update with command: " << command << std::endl);
       }
     }
 
 
   //
   // Now update repository and remember what files were updated
-  // 
-  cmGeneratedFileStream os; 
+  //
+  cmGeneratedFileStream os;
   if ( !this->StartResultingXML("Update", os) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open log file" << std::endl);
+    cmCTestLog(this->CTest, ERROR_MESSAGE, "Cannot open log file"
+      << std::endl);
     }
-  std::string start_time = m_CTest->CurrentTime();
+  std::string start_time = this->CTest->CurrentTime();
   double elapsed_time_start = cmSystemTools::GetTime();
 
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "* Update repository: "
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "* Update repository: "
     << command.c_str() << std::endl);
-  if ( !m_CTest->GetShowOnly() )
+  if ( !this->CTest->GetShowOnly() )
     {
     command = "";
     switch( updateType )
@@ -496,8 +506,8 @@ int cmCTestUpdateHandler::ProcessHandler()
         " " + extra_update_opts;
       ofs << "* Update repository: " << std::endl;
       ofs << "  Command: " << command.c_str() << std::endl;
-      res = m_CTest->RunCommand(command.c_str(), &goutput, &errors,
-        &retVal, sourceDirectory, 0 /*m_TimeOut*/);
+      res = this->CTest->RunCommand(command.c_str(), &goutput, &errors,
+        &retVal, sourceDirectory, 0 /*this->TimeOut*/);
       ofs << "  Output: " << goutput.c_str() << std::endl;
       ofs << "  Errors: " << errors.c_str() << std::endl;
       break;
@@ -508,17 +518,17 @@ int cmCTestUpdateHandler::ProcessHandler()
           " " + extra_update_opts;
         ofs << "* Update repository: " << std::endl;
         ofs << "  Command: " << command.c_str() << std::endl;
-        bool res1 = m_CTest->RunCommand(command.c_str(), &partialOutput,
+        bool res1 = this->CTest->RunCommand(command.c_str(), &partialOutput,
           &errors,
-          &retVal, sourceDirectory, 0 /*m_TimeOut*/);
+          &retVal, sourceDirectory, 0 /*this->TimeOut*/);
         ofs << "  Output: " << partialOutput.c_str() << std::endl;
         ofs << "  Errors: " << errors.c_str() << std::endl;
         goutput = partialOutput;
         command = updateCommand + " status";
         ofs << "* Status repository: " << std::endl;
         ofs << "  Command: " << command.c_str() << std::endl;
-        res = m_CTest->RunCommand(command.c_str(), &partialOutput, &errors,
-          &retVal, sourceDirectory, 0 /*m_TimeOut*/);
+        res = this->CTest->RunCommand(command.c_str(), &partialOutput,
+          &errors, &retVal, sourceDirectory, 0 /*this->TimeOut*/);
         ofs << "  Output: " << partialOutput.c_str() << std::endl;
         ofs << "  Errors: " << errors.c_str() << std::endl;
         goutput += partialOutput;
@@ -541,15 +551,15 @@ int cmCTestUpdateHandler::ProcessHandler()
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     << "<Update mode=\"Client\" Generator=\"ctest-"
     << cmVersion::GetCMakeVersion() << "\">\n"
-    << "\t<Site>" << m_CTest->GetCTestConfiguration("Site") << "</Site>\n"
-    << "\t<BuildName>" << m_CTest->GetCTestConfiguration("BuildName")
+    << "\t<Site>" << this->CTest->GetCTestConfiguration("Site") << "</Site>\n"
+    << "\t<BuildName>" << this->CTest->GetCTestConfiguration("BuildName")
     << "</BuildName>\n"
-    << "\t<BuildStamp>" << m_CTest->GetCurrentTag() << "-"
-    << m_CTest->GetTestModelString() << "</BuildStamp>" << std::endl;
+    << "\t<BuildStamp>" << this->CTest->GetCurrentTag() << "-"
+    << this->CTest->GetTestModelString() << "</BuildStamp>" << std::endl;
   os << "\t<StartDateTime>" << start_time << "</StartDateTime>\n"
-    << "\t<UpdateCommand>" << m_CTest->MakeXMLSafe(command)
+    << "\t<UpdateCommand>" << this->CTest->MakeXMLSafe(command)
     << "</UpdateCommand>\n"
-    << "\t<UpdateType>" << m_CTest->MakeXMLSafe(
+    << "\t<UpdateType>" << this->CTest->MakeXMLSafe(
       cmCTestUpdateHandlerUpdateToString(updateType))
     << "</UpdateType>\n";
 
@@ -584,9 +594,9 @@ int cmCTestUpdateHandler::ProcessHandler()
   bool first_file = true;
 
   cmCTestUpdateHandler::AuthorsToUpdatesMap authors_files_map;
-  int num_updated = 0;
-  int num_modified = 0;
-  int num_conflicting = 0;
+  int numUpdated = 0;
+  int numModiefied = 0;
+  int numConflicting = 0;
   // In subversion, get the latest revision
   if ( updateType == cmCTestUpdateHandler::e_SVN )
     {
@@ -601,19 +611,20 @@ int cmCTestUpdateHandler::ProcessHandler()
       }
     if ( svn_latest_revision <= 0 )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem determining the current "
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
+        "Problem determining the current "
         "revision of the repository from output:" << std::endl
         << goutput.c_str() << std::endl);
       }
     else
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT,
+      cmCTestLog(this->CTest, HANDLER_OUTPUT,
         "   Current revision of repository is: " << svn_latest_revision
         << std::endl);
       }
     }
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT,
+  cmCTestLog(this->CTest, HANDLER_OUTPUT,
     "   Gathering version information (each . represents one updated file):"
     << std::endl);
   int file_count = 0;
@@ -630,9 +641,9 @@ int cmCTestUpdateHandler::ProcessHandler()
       {
       if ( file_count == 0 )
         {
-        cmCTestLog(m_CTest, HANDLER_OUTPUT, "    " << std::flush);
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, "    " << std::flush);
         }
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, "." << std::flush);
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "." << std::flush);
       std::string upChar = file_update_line.match(1);
       std::string upFile = file_update_line.match(2);
       char mod = upChar[0];
@@ -647,7 +658,7 @@ int cmCTestUpdateHandler::ProcessHandler()
         modifiedOrConflict = true;
         }
       const char* file = upFile.c_str();
-      cmCTestLog(m_CTest, DEBUG, "Line" << cc << ": " << mod << " - "
+      cmCTestLog(this->CTest, DEBUG, "Line" << cc << ": " << mod << " - "
         << file << std::endl);
 
       std::string output;
@@ -677,14 +688,14 @@ int cmCTestUpdateHandler::ProcessHandler()
             }
           break;
           }
-        cmCTestLog(m_CTest, DEBUG, "Do log: " << logcommand << std::endl);
-        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+        cmCTestLog(this->CTest, DEBUG, "Do log: " << logcommand << std::endl);
+        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
           "* Get file update information: " << logcommand.c_str()
           << std::endl);
         ofs << "* Get log information for file: " << file << std::endl;
         ofs << "  Command: " << logcommand.c_str() << std::endl;
-        res = m_CTest->RunCommand(logcommand.c_str(), &output, &errors,
-          &retVal, sourceDirectory, 0 /*m_TimeOut*/);
+        res = this->CTest->RunCommand(logcommand.c_str(), &output, &errors,
+          &retVal, sourceDirectory, 0 /*this->TimeOut*/);
         ofs << "  Output: " << output.c_str() << std::endl;
         ofs << "  Errors: " << errors.c_str() << std::endl;
         if ( ofs )
@@ -694,7 +705,7 @@ int cmCTestUpdateHandler::ProcessHandler()
         }
       if ( res && retVal == 0)
         {
-        cmCTestLog(m_CTest, DEBUG, output << std::endl);
+        cmCTestLog(this->CTest, DEBUG, output << std::endl);
         std::string::size_type sline = 0;
         std::string srevision1 = "Unknown";
         std::string sdate1     = "Unknown";
@@ -778,13 +789,13 @@ int cmCTestUpdateHandler::ProcessHandler()
             srevision1 = str.str();
             if (!svn_status_line_regex.find(output))
               {
-              cmCTestLog(m_CTest, ERROR_MESSAGE,
+              cmCTestLog(this->CTest, ERROR_MESSAGE,
                 "Bad output from SVN status command: " << output
                 << std::endl);
               }
             else if ( svn_status_line_regex.match(4) != file )
               {
-              cmCTestLog(m_CTest, ERROR_MESSAGE,
+              cmCTestLog(this->CTest, ERROR_MESSAGE,
                 "Bad output from SVN status command. "
                 "The file name returned: \""
                 << svn_status_line_regex.match(4)
@@ -812,27 +823,27 @@ int cmCTestUpdateHandler::ProcessHandler()
               int maxrev = parser.GetMaxRevision();
               cmCTestUpdateHandlerSVNXMLParser::
                 t_VectorOfCommits::iterator it;
-              for ( it = parser.GetCommits()->begin(); 
-                it != parser.GetCommits()->end(); 
+              for ( it = parser.GetCommits()->begin();
+                it != parser.GetCommits()->end();
                 ++ it )
                 {
-                if ( it->m_Revision == maxrev )
+                if ( it->Revision == maxrev )
                   {
                   cmOStringStream mRevStream;
                   mRevStream << maxrev;
                   srevision1 = mRevStream.str();
-                  sauthor1 = it->m_Author;
-                  comment1 = it->m_Message;
-                  sdate1 = it->m_Date;
+                  sauthor1 = it->Author;
+                  comment1 = it->Message;
+                  sdate1 = it->Date;
                   }
-                else if ( it->m_Revision == minrev )
+                else if ( it->Revision == minrev )
                   {
                   cmOStringStream mRevStream;
                   mRevStream << minrev;
                   srevision2 = mRevStream.str();
-                  sauthor2 = it->m_Author;
-                  comment2 = it->m_Message;       
-                  sdate2 = it->m_Date;
+                  sauthor2 = it->Author;
+                  comment2 = it->Message;
+                  sdate2 = it->Date;
                   }
                 }
               }
@@ -869,30 +880,30 @@ int cmCTestUpdateHandler::ProcessHandler()
           }
         if ( mod == 'C' )
           {
-          num_conflicting ++;
+          numConflicting ++;
           os << "\t<Conflicting>" << std::endl;
           }
         else if ( mod == 'G' )
           {
-          num_conflicting ++;
+          numConflicting ++;
           os << "\t<Conflicting>" << std::endl;
           }
         else if ( mod == 'M' )
           {
-          num_modified ++;
+          numModiefied ++;
           os << "\t<Modified>" << std::endl;
           }
         else
           {
-          num_updated ++;
+          numUpdated ++;
           os << "\t<Updated>" << std::endl;
           }
         if ( srevision2 == "Unknown" )
           {
           srevision2 = srevision1;
           }
-        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "File: " << path.c_str()
-          << " / " << fname.c_str() << " was updated by "
+        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "File: "
+          << path.c_str() << " / " << fname.c_str() << " was updated by "
           << sauthor1.c_str() << " to revision: " << srevision1.c_str()
           << " from revision: " << srevision2.c_str() << std::endl);
         os << "\t\t<File Directory=\"" << cmCTest::MakeXMLSafe(path) << "\">"
@@ -968,28 +979,28 @@ int cmCTestUpdateHandler::ProcessHandler()
     }
   if ( file_count )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
     }
-  if ( num_updated )
+  if ( numUpdated )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_updated
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Found " << numUpdated
       << " updated files" << std::endl);
     }
-  if ( num_modified )
+  if ( numModiefied )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_modified
-      << " locally modified files" 
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Found " << numModiefied
+      << " locally modified files"
       << std::endl);
     }
-  if ( num_conflicting )
+  if ( numConflicting )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_conflicting
-      << " conflicting files" 
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Found " << numConflicting
+      << " conflicting files"
       << std::endl);
     }
-  if ( num_modified == 0 && num_conflicting == 0 && num_updated == 0 )
+  if ( numModiefied == 0 && numConflicting == 0 && numUpdated == 0 )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Project is up-to-date"
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Project is up-to-date"
       << std::endl);
     }
   if ( !first_file )
@@ -1013,36 +1024,37 @@ int cmCTestUpdateHandler::ProcessHandler()
     os << "\t</Author>" << std::endl;
     }
 
-  cmCTestLog(m_CTest, DEBUG, "End" << std::endl);
-  std::string end_time = m_CTest->CurrentTime();
+  cmCTestLog(this->CTest, DEBUG, "End" << std::endl);
+  std::string end_time = this->CTest->CurrentTime();
   os << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
-    << "<ElapsedMinutes>" << 
-    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0 
+    << "<ElapsedMinutes>" <<
+    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0
     << "</ElapsedMinutes>\n"
     << "\t<UpdateReturnStatus>";
-  if ( num_modified > 0 || num_conflicting > 0 )
+  if ( numModiefied > 0 || numConflicting > 0 )
     {
     os << "Update error: There are modified or conflicting files in the "
       "repository";
-    cmCTestLog(m_CTest, ERROR_MESSAGE,
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
       "   There are modified or conflicting files in the repository"
       << std::endl);
     }
   if ( updateProducedError )
     {
     os << "Update error: ";
-    os << m_CTest->MakeXMLSafe(checkoutErrorMessages);
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "   Update with command: " << command
-      << " failed" << std::endl);
+    os << this->CTest->MakeXMLSafe(checkoutErrorMessages);
+    cmCTestLog(this->CTest, ERROR_MESSAGE, "   Update with command: "
+      << command << " failed" << std::endl);
     }
   os << "</UpdateReturnStatus>" << std::endl;
   os << "</Update>" << std::endl;
 
   if (! res || retVal )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Error(s) when updating the project"
-      << std::endl);
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Output: " << goutput << std::endl);
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+      "Error(s) when updating the project" << std::endl);
+    cmCTestLog(this->CTest, ERROR_MESSAGE, "Output: "
+      << goutput << std::endl);
     return -1;
     }
   return count;