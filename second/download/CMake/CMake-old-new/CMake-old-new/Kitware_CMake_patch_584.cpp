@@ -51,7 +51,7 @@ class cmCTestUpdateHandlerSVNXMLParser : public cmXMLParser
     std::string m_Message;
     };
   cmCTestUpdateHandlerSVNXMLParser(cmCTestUpdateHandler* up)
-    : cmXMLParser(), m_UpdateHandler(up), m_MinRevision(-1), m_MaxRevision(-1), m_Verbose(false)
+    : cmXMLParser(), m_UpdateHandler(up), m_MinRevision(-1), m_MaxRevision(-1)
     {
     }
 
@@ -73,8 +73,6 @@ class cmCTestUpdateHandlerSVNXMLParser : public cmXMLParser
   int GetMinRevision() { return m_MinRevision; }
   int GetMaxRevision() { return m_MaxRevision; }
 
-  void SetVerbose(bool v) { m_Verbose = v; }
-
 protected:
   void StartElement(const char* name, const char** atts)
     {
@@ -101,13 +99,10 @@ class cmCTestUpdateHandlerSVNXMLParser : public cmXMLParser
     {
     if ( strcmp(name, "logentry") == 0 )
       {
-      if ( m_Verbose )
-        {
-        std::cout << "\tRevision: " << m_CommitLog.m_Revision<< std::endl;
-        std::cout << "\tAuthor:   " << m_CommitLog.m_Author.c_str() << std::endl;
-        std::cout << "\tDate:     " << m_CommitLog.m_Date.c_str() << std::endl;
-        std::cout << "\tMessage:  " << m_CommitLog.m_Message.c_str() << std::endl;
-        }
+      cmCTestLog(m_UpdateHandler->GetCTestInstance(), HANDLER_VERBOSE_OUTPUT, "\tRevision: " << m_CommitLog.m_Revision<< std::endl
+        << "\tAuthor:   " << m_CommitLog.m_Author.c_str() << std::endl
+        << "\tDate:     " << m_CommitLog.m_Date.c_str() << std::endl
+        << "\tMessage:  " << m_CommitLog.m_Message.c_str() << std::endl);
       m_Commits.push_back(m_CommitLog);
       }
     else if ( strcmp(name, "author") == 0 )
@@ -154,15 +149,13 @@ class cmCTestUpdateHandlerSVNXMLParser : public cmXMLParser
   t_VectorOfCommits m_Commits;
   int m_MinRevision;
   int m_MaxRevision;
-  bool m_Verbose;
 };
 //**********************************************************************
 //----------------------------------------------------------------------
 
 //----------------------------------------------------------------------
 cmCTestUpdateHandler::cmCTestUpdateHandler()
 {
-  m_Verbose = false; 
   m_CTest = 0;
 }
 
@@ -211,11 +204,11 @@ int cmCTestUpdateHandler::ProcessHandler()
   const char* sourceDirectory = this->GetOption("SourceDirectory");
   if ( !sourceDirectory )
     {
-    std::cerr << "Cannot find SourceDirectory  key in the DartConfiguration.tcl" << std::endl;
+    cmCTestLog(m_CTest, ERROR, "Cannot find SourceDirectory  key in the DartConfiguration.tcl" << std::endl);
     return -1;
     }
 
-  std::cout << "Updating the repository: " << sourceDirectory << std::endl;
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "Updating the repository: " << sourceDirectory << std::endl);
 
   // Get update command
   std::string updateCommand = m_CTest->GetCTestConfiguration("UpdateCommand");
@@ -227,7 +220,7 @@ int cmCTestUpdateHandler::ProcessHandler()
       updateCommand = m_CTest->GetCTestConfiguration("SVNCommand");
       if ( updateCommand.empty() )
         {
-        std::cerr << "Cannot find CVSCommand, SVNCommand, or UpdateCommand key in the DartConfiguration.tcl" << std::endl;
+        cmCTestLog(m_CTest, ERROR, "Cannot find CVSCommand, SVNCommand, or UpdateCommand key in the DartConfiguration.tcl" << std::endl);
         return -1;
         }
       else
@@ -264,8 +257,8 @@ int cmCTestUpdateHandler::ProcessHandler()
   std::string extra_update_opts;
   if ( m_CTest->GetTestModel() == cmCTest::NIGHTLY )
     {
-    struct tm* t = cmCTest::GetNightlyTime(m_CTest->GetCTestConfiguration("NightlyStartTime"),
-      m_Verbose, m_CTest->GetTomorrowTag());
+    struct tm* t = m_CTest->GetNightlyTime(m_CTest->GetCTestConfiguration("NightlyStartTime"),
+      m_CTest->GetTomorrowTag());
     char current_time[1024];
     sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
       t->tm_year + 1900,
@@ -324,15 +317,12 @@ int cmCTestUpdateHandler::ProcessHandler()
   //
   if ( !command.empty() )
     {
-    if ( m_Verbose )
-      {
-      std::cout << "* Get repository information: " << command.c_str() << std::endl;
-      }
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "* Get repository information: " << command.c_str() << std::endl);
     if ( !m_CTest->GetShowOnly() )
       {
       res = cmSystemTools::RunSingleCommand(command.c_str(), &goutput, 
         &retVal, sourceDirectory,
-        m_Verbose, 0 /*m_TimeOut*/);
+        m_HandlerVerbose, 0 /*m_TimeOut*/);
       if ( ofs )
         {
         ofs << "--- Update information ---" << std::endl;
@@ -350,15 +340,15 @@ int cmCTestUpdateHandler::ProcessHandler()
             {
             std::string currentRevisionString = current_revision_regex.match(1);
             svn_current_revision = atoi(currentRevisionString.c_str());
-            std::cout << "   Old revision of repository is: " << svn_current_revision << std::endl;
+            cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Old revision of repository is: " << svn_current_revision << std::endl);
             }
           }
         break;
         }
       }
     else
       {
-      std::cout << "Update with command: " << command << std::endl;
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Update with command: " << command << std::endl);
       }
     }
 
@@ -369,15 +359,12 @@ int cmCTestUpdateHandler::ProcessHandler()
   cmGeneratedFileStream os; 
   if ( !m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), "Update.xml", os, true) )
     {
-    std::cerr << "Cannot open log file" << std::endl;
+    cmCTestLog(m_CTest, ERROR, "Cannot open log file" << std::endl);
     }
   std::string start_time = m_CTest->CurrentTime();
   double elapsed_time_start = cmSystemTools::GetTime();
 
-  if ( m_Verbose )
-    {
-    std::cout << "* Update repository: " << command.c_str() << std::endl;
-    }
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "* Update repository: " << command.c_str() << std::endl);
   if ( !m_CTest->GetShowOnly() )
     {
     command = "";
@@ -388,7 +375,7 @@ int cmCTestUpdateHandler::ProcessHandler()
         " " + extra_update_opts;
       res = cmSystemTools::RunSingleCommand(command.c_str(), &goutput, 
         &retVal, sourceDirectory,
-        m_Verbose, 0 /*m_TimeOut*/);
+        m_HandlerVerbose, 0 /*m_TimeOut*/);
       break;
     case cmCTestUpdateHandler::e_SVN:
         {
@@ -397,11 +384,11 @@ int cmCTestUpdateHandler::ProcessHandler()
           " " + extra_update_opts;
         bool res1 = cmSystemTools::RunSingleCommand(command.c_str(), &partialOutput, 
           &retVal, sourceDirectory,
-          m_Verbose, 0 /*m_TimeOut*/);
+          m_HandlerVerbose, 0 /*m_TimeOut*/);
         command = updateCommand + " status";
         res = cmSystemTools::RunSingleCommand(command.c_str(), &partialOutput, 
           &retVal, sourceDirectory,
-          m_Verbose, 0 /*m_TimeOut*/);
+          m_HandlerVerbose, 0 /*m_TimeOut*/);
         goutput += partialOutput;
         res = res && res1;
         }
@@ -465,26 +452,21 @@ int cmCTestUpdateHandler::ProcessHandler()
     }
   if ( updateType == cmCTestUpdateHandler::e_SVN )
     {
-    std::cout << "   Current revision of repository is: " << svn_latest_revision << std::endl;
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Current revision of repository is: " << svn_latest_revision << std::endl);
     }
 
-  std::cout << "   Gathering version information (each . represents one updated file):" << std::endl;
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Gathering version information (each . represents one updated file):" << std::endl);
   int file_count = 0;
   for ( cc= 0 ; cc < lines.size(); cc ++ )
     {
     const char* line = lines[cc].c_str();
     if ( file_update_line.find(line) )
       {
-      if ( !m_Verbose )
+      if ( file_count == 0 )
         {
-        if ( file_count == 0 )
-          {
-          std::cout << "    ";
-          std::cout.flush();
-          }
-        std::cout << ".";
+        cmCTestLog(m_CTest, HANDLER_OUTPUT, "    " << std::flush);
         }
-      std::cout.flush();
+      cmCTestLog(m_CTest, HANDLER_OUTPUT, "." << std::flush);
       std::string upChar = file_update_line.match(1);
       std::string upFile = file_update_line.match(2);
       char mod = upChar[0];
@@ -495,7 +477,7 @@ int cmCTestUpdateHandler::ProcessHandler()
         modifiedOrConflict = true;
         }
       const char* file = upFile.c_str();
-      //std::cout << "Line" << cc << ": " << mod << " - " << file << std::endl;
+      cmCTestLog(m_CTest, DEBUG, "Line" << cc << ": " << mod << " - " << file << std::endl);
 
       std::string output;
       if ( modifiedOrConflict )
@@ -521,22 +503,19 @@ int cmCTestUpdateHandler::ProcessHandler()
             }
           break;
           }
-        //std::cout << "Do log: " << logcommand << std::endl;
-        if ( m_Verbose )
-          {
-          std::cout << "* Get file update information: " << logcommand.c_str() << std::endl;
-          }
+        cmCTestLog(m_CTest, DEBUG, "Do log: " << logcommand << std::endl);
+        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "* Get file update information: " << logcommand.c_str() << std::endl);
         res = cmSystemTools::RunSingleCommand(logcommand.c_str(), &output, 
           &retVal, sourceDirectory,
-          m_Verbose, 0 /*m_TimeOut*/);
+          m_HandlerVerbose, 0 /*m_TimeOut*/);
         if ( ofs )
           {
           ofs << output << std::endl;
           }
         }
       if ( res && retVal == 0)
         {
-        //std::cout << output << std::endl;
+        cmCTestLog(m_CTest, DEBUG, output << std::endl);
         std::string::size_type sline = 0;
         std::string srevision1 = "Unknown";
         std::string sdate1     = "Unknown";
@@ -618,11 +597,11 @@ int cmCTestUpdateHandler::ProcessHandler()
             srevision1 = str.str();
             if (!svn_status_line_regex.find(output))
               {
-              std::cerr << "Bad output from SVN status command: " << output << std::endl;
+              cmCTestLog(m_CTest, ERROR, "Bad output from SVN status command: " << output << std::endl);
               }
             else if ( svn_status_line_regex.match(4) != file )
               {
-              std::cerr << "Bad output from SVN status command. The file name returned: \"" << svn_status_line_regex.match(4) << "\" was different than the file specified: \"" << file << "\"" << std::endl;
+              cmCTestLog(m_CTest, ERROR, "Bad output from SVN status command. The file name returned: \"" << svn_status_line_regex.match(4) << "\" was different than the file specified: \"" << file << "\"" << std::endl);
               }
             else
               {
@@ -638,7 +617,6 @@ int cmCTestUpdateHandler::ProcessHandler()
           else
             {
             cmCTestUpdateHandlerSVNXMLParser parser(this);
-            parser.SetVerbose(m_Verbose);
             if ( parser.Parse(output.c_str()) )
               {
               int minrev = parser.GetMinRevision();
@@ -719,12 +697,9 @@ int cmCTestUpdateHandler::ProcessHandler()
           {
           srevision2 = srevision1;
           }
-        if ( m_Verbose )
-          {
-          std::cout << "File: " << path.c_str() << " / " << fname.c_str() << " was updated by "
-            << sauthor1.c_str() << " to revision: " << srevision1.c_str()
-            << " from revision: " << srevision2.c_str() << std::endl;
-          }
+        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "File: " << path.c_str() << " / " << fname.c_str() << " was updated by "
+          << sauthor1.c_str() << " to revision: " << srevision1.c_str()
+          << " from revision: " << srevision2.c_str() << std::endl);
         os << "\t\t<File Directory=\"" << cmCTest::MakeXMLSafe(path) << "\">" << cmCTest::MakeXMLSafe(fname)
           << "</File>\n"
           << "\t\t<Directory>" << cmCTest::MakeXMLSafe(path) << "</Directory>\n"
@@ -785,25 +760,25 @@ int cmCTestUpdateHandler::ProcessHandler()
     }
   if ( file_count )
     {
-    std::cout << std::endl;
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl);
     }
   if ( num_updated )
     {
-    std::cout << "   Found " << num_updated << " updated files" << std::endl;
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_updated << " updated files" << std::endl);
     }
   if ( num_modified )
     {
-    std::cout << "   Found " << num_modified << " locally modified files" 
-      << std::endl;
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_modified << " locally modified files" 
+      << std::endl);
     }
   if ( num_conflicting )
     {
-    std::cout << "   Found " << num_conflicting << " conflicting files" 
-      << std::endl;
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_conflicting << " conflicting files" 
+      << std::endl);
     }
   if ( num_modified == 0 && num_conflicting == 0 && num_updated == 0 )
     {
-    std::cout << "   Project is up-to-date" << std::endl;
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Project is up-to-date" << std::endl);
     }
   if ( !first_file )
     {
@@ -826,7 +801,7 @@ int cmCTestUpdateHandler::ProcessHandler()
     os << "\t</Author>" << std::endl;
     }
 
-  //std::cout << "End" << std::endl;
+  cmCTestLog(m_CTest, DEBUG, "End" << std::endl);
   std::string end_time = m_CTest->CurrentTime();
   os << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
     << "<ElapsedMinutes>" << 
@@ -836,13 +811,13 @@ int cmCTestUpdateHandler::ProcessHandler()
   if ( num_modified > 0 || num_conflicting > 0 )
     {
     os << "Update error: There are modified or conflicting files in the repository";
-    std::cerr << "   There are modified or conflicting files in the repository" << std::endl;
+    cmCTestLog(m_CTest, ERROR, "   There are modified or conflicting files in the repository" << std::endl);
     }
   if ( updateProducedError )
     {
     os << "Update error: ";
     os << m_CTest->MakeXMLSafe(goutput);
-    std::cerr << "   Update with command: " << command << " failed" << std::endl;
+    cmCTestLog(m_CTest, ERROR, "   Update with command: " << command << " failed" << std::endl);
     }
   os << "</UpdateReturnStatus>" << std::endl;
   os << "</Update>" << std::endl;
@@ -854,8 +829,8 @@ int cmCTestUpdateHandler::ProcessHandler()
 
   if (! res || retVal )
     {
-    std::cerr << "Error(s) when updating the project" << std::endl;
-    std::cerr << "Output: " << goutput << std::endl;
+    cmCTestLog(m_CTest, ERROR, "Error(s) when updating the project" << std::endl);
+    cmCTestLog(m_CTest, ERROR, "Output: " << goutput << std::endl);
     return -1;
     }
   return count;