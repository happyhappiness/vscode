@@ -48,7 +48,8 @@ static const char* cmCTestUpdateHandlerUpdateStrings[] =
 
 static const char* cmCTestUpdateHandlerUpdateToString(int type)
 {
-  if ( type < cmCTestUpdateHandler::e_UNKNOWN || type >= cmCTestUpdateHandler::e_LAST )
+  if ( type < cmCTestUpdateHandler::e_UNKNOWN ||
+    type >= cmCTestUpdateHandler::e_LAST )
     {
     return cmCTestUpdateHandlerUpdateStrings[cmCTestUpdateHandler::e_UNKNOWN];
     }
@@ -116,23 +117,27 @@ class cmCTestUpdateHandlerSVNXMLParser : public cmXMLParser
     {
     if ( strcmp(name, "logentry") == 0 )
       {
-      cmCTestLog(m_UpdateHandler->GetCTestInstance(), HANDLER_VERBOSE_OUTPUT, "\tRevision: " << m_CommitLog.m_Revision<< std::endl
+      cmCTestLog(m_UpdateHandler->GetCTestInstance(), HANDLER_VERBOSE_OUTPUT,
+        "\tRevision: " << m_CommitLog.m_Revision<< std::endl
         << "\tAuthor:   " << m_CommitLog.m_Author.c_str() << std::endl
         << "\tDate:     " << m_CommitLog.m_Date.c_str() << std::endl
         << "\tMessage:  " << m_CommitLog.m_Message.c_str() << std::endl);
       m_Commits.push_back(m_CommitLog);
       }
     else if ( strcmp(name, "author") == 0 )
       {
-      m_CommitLog.m_Author.assign(&(*(m_CharacterData.begin())), m_CharacterData.size());
+      m_CommitLog.m_Author.assign(&(*(m_CharacterData.begin())),
+        m_CharacterData.size());
       }
     else if ( strcmp(name, "date") == 0 )
       {
-      m_CommitLog.m_Date.assign(&(*(m_CharacterData.begin())), m_CharacterData.size());
+      m_CommitLog.m_Date.assign(&(*(m_CharacterData.begin())),
+        m_CharacterData.size());
       }
     else if ( strcmp(name, "msg") == 0 )
       {
-      m_CommitLog.m_Message.assign(&(*(m_CharacterData.begin())), m_CharacterData.size());
+      m_CommitLog.m_Message.assign(&(*(m_CharacterData.begin())),
+        m_CharacterData.size());
       }
     m_CharacterData.erase(m_CharacterData.begin(), m_CharacterData.end());
     }
@@ -184,7 +189,8 @@ void cmCTestUpdateHandler::Initialize()
 //----------------------------------------------------------------------
 int cmCTestUpdateHandler::DetermineType(const char* cmd, const char* type)
 {
-  cmCTestLog(m_CTest, DEBUG, "Determine update type from command: " << cmd << " and type: " << type << std::endl);
+  cmCTestLog(m_CTest, DEBUG, "Determine update type from command: " << cmd
+    << " and type: " << type << std::endl);
   if ( type && *type )
     {
     cmCTestLog(m_CTest, DEBUG, "Type specified: " << type << std::endl);
@@ -200,7 +206,8 @@ int cmCTestUpdateHandler::DetermineType(const char* cmd, const char* type)
     }
   else
     {
-    cmCTestLog(m_CTest, DEBUG, "Type not specified, check command: " << cmd << std::endl);
+    cmCTestLog(m_CTest, DEBUG, "Type not specified, check command: " << cmd
+      << std::endl);
     std::string stype = cmSystemTools::LowerCase(cmd);
     if ( stype.find("cvs") != std::string::npos )
       {
@@ -212,7 +219,8 @@ int cmCTestUpdateHandler::DetermineType(const char* cmd, const char* type)
       }
     }
   std::string sourceDirectory = this->GetOption("SourceDirectory");
-  cmCTestLog(m_CTest, DEBUG, "Check directory: " << sourceDirectory.c_str() << std::endl);
+  cmCTestLog(m_CTest, DEBUG, "Check directory: " << sourceDirectory.c_str()
+    << std::endl);
   sourceDirectory += "/.svn";
   if ( cmSystemTools::FileExists(sourceDirectory.c_str()) )
     {
@@ -246,7 +254,9 @@ int cmCTestUpdateHandler::ProcessHandler()
   const char* sourceDirectory = this->GetOption("SourceDirectory");
   if ( !sourceDirectory )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot find SourceDirectory  key in the DartConfiguration.tcl" << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE,
+      "Cannot find SourceDirectory  key in the DartConfiguration.tcl"
+      << std::endl);
     return -1;
     }
 
@@ -261,39 +271,49 @@ int cmCTestUpdateHandler::ProcessHandler()
   const char* initialCheckoutCommand = this->GetOption("InitialCheckout");
   if ( initialCheckoutCommand )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   First perform the initil checkout: " << initialCheckoutCommand << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT,
+      "   First perform the initil checkout: " << initialCheckoutCommand
+      << std::endl);
     cmStdString parent = cmSystemTools::GetParentDirectory(sourceDirectory);
     if ( parent.empty() )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE,
-        "Something went wrong when trying to determine the parent directory of " << sourceDirectory << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Something went wrong when trying "
+        "to determine the parent directory of " << sourceDirectory
+        << std::endl);
       return -1;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Perform checkout in directory: " << parent.c_str() << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Perform checkout in directory: "
+      << parent.c_str() << std::endl);
     if ( !cmSystemTools::MakeDirectory(parent.c_str()) )
       {
       cmCTestLog(m_CTest, ERROR_MESSAGE,
-        "Cannot create parent directory: " << parent.c_str() << " of the source directory: " << sourceDirectory << std::endl);
+        "Cannot create parent directory: " << parent.c_str()
+        << " of the source directory: " << sourceDirectory << std::endl);
       return -1;
       }
     ofs << "* Run initial checkout" << std::endl;
     ofs << "  Command: " << initialCheckoutCommand << std::endl;
-    cmCTestLog(m_CTest, DEBUG, "   Before: " << initialCheckoutCommand << std::endl);
-    bool retic = m_CTest->RunCommand(initialCheckoutCommand, &goutput, &errors, &retVal, parent.c_str(), 0 /* Timeout */);
-    cmCTestLog(m_CTest, DEBUG, "   After: " << initialCheckoutCommand << std::endl);
+    cmCTestLog(m_CTest, DEBUG, "   Before: "
+      << initialCheckoutCommand << std::endl);
+    bool retic = m_CTest->RunCommand(initialCheckoutCommand, &goutput,
+      &errors, &retVal, parent.c_str(), 0 /* Timeout */);
+    cmCTestLog(m_CTest, DEBUG, "   After: "
+      << initialCheckoutCommand << std::endl);
     ofs << "  Output: " << goutput.c_str() << std::endl;
     ofs << "  Errors: " << errors.c_str() << std::endl;
     if ( !retic || retVal )
       {
       cmOStringStream ostr;
-      ostr << "Problem running initial checkout Output [" << goutput << "] Errors [" << errors << "]";
+      ostr << "Problem running initial checkout Output [" << goutput
+        << "] Errors [" << errors << "]";
       cmCTestLog(m_CTest, ERROR_MESSAGE, ostr.str().c_str() << std::endl);
       checkoutErrorMessages += ostr.str();
       updateProducedError = true;
       }
     m_CTest->InitializeFromCommand(m_Command);
     }
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Updating the repository: " << sourceDirectory << std::endl);
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Updating the repository: "
+    << sourceDirectory << std::endl);
 
   // Get update command
   std::string updateCommand = m_CTest->GetCTestConfiguration("UpdateCommand");
@@ -305,7 +325,9 @@ int cmCTestUpdateHandler::ProcessHandler()
       updateCommand = m_CTest->GetCTestConfiguration("SVNCommand");
       if ( updateCommand.empty() )
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot find CVSCommand, SVNCommand, or UpdateCommand key in the DartConfiguration.tcl" << std::endl);
+        cmCTestLog(m_CTest, ERROR_MESSAGE,
+          "Cannot find CVSCommand, SVNCommand, or UpdateCommand key in the "
+          "DartConfiguration.tcl" << std::endl);
         return -1;
         }
       else
@@ -320,10 +342,13 @@ int cmCTestUpdateHandler::ProcessHandler()
     }
   else
     {
-    updateType = this->DetermineType(updateCommand.c_str(), m_CTest->GetCTestConfiguration("UpdateType").c_str());
+    updateType = this->DetermineType(updateCommand.c_str(),
+      m_CTest->GetCTestConfiguration("UpdateType").c_str());
     }
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Use " << cmCTestUpdateHandlerUpdateToString(updateType) << " repository type" << std::endl;);
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Use "
+    << cmCTestUpdateHandlerUpdateToString(updateType) << " repository type"
+    << std::endl;);
 
   // And update options
   std::string updateOptions = m_CTest->GetCTestConfiguration("UpdateOptions");
@@ -348,7 +373,8 @@ int cmCTestUpdateHandler::ProcessHandler()
   std::string extra_update_opts;
   if ( m_CTest->GetTestModel() == cmCTest::NIGHTLY )
     {
-    struct tm* t = m_CTest->GetNightlyTime(m_CTest->GetCTestConfiguration("NightlyStartTime"),
+    struct tm* t = m_CTest->GetNightlyTime(
+      m_CTest->GetCTestConfiguration("NightlyStartTime"),
       m_CTest->GetTomorrowTag());
     char current_time[1024];
     sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
@@ -396,11 +422,13 @@ int cmCTestUpdateHandler::ProcessHandler()
 
 
   //
-  // Get initial repository information if that is possible. With subversion, this will check the current revision.
+  // Get initial repository information if that is possible. With subversion,
+  // this will check the current revision.
   //
   if ( !command.empty() )
     {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "* Get repository information: " << command.c_str() << std::endl);
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+        "* Get repository information: " << command.c_str() << std::endl);
     if ( !m_CTest->GetShowOnly() )
       {
       ofs << "* Get repository information" << std::endl;
@@ -422,20 +450,25 @@ int cmCTestUpdateHandler::ProcessHandler()
         break;
       case cmCTestUpdateHandler::e_SVN:
           {
-          cmsys::RegularExpression current_revision_regex("Revision: ([0-9]+)");
+          cmsys::RegularExpression current_revision_regex(
+            "Revision: ([0-9]+)");
           if ( current_revision_regex.find(goutput.c_str()) )
             {
-            std::string currentRevisionString = current_revision_regex.match(1);
+            std::string currentRevisionString
+              = current_revision_regex.match(1);
             svn_current_revision = atoi(currentRevisionString.c_str());
-            cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Old revision of repository is: " << svn_current_revision << std::endl);
+            cmCTestLog(m_CTest, HANDLER_OUTPUT,
+              "   Old revision of repository is: " << svn_current_revision
+              << std::endl);
             }
           }
         break;
         }
       }
     else
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Update with command: " << command << std::endl);
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+        "Update with command: " << command << std::endl);
       }
     }
 
@@ -451,7 +484,8 @@ int cmCTestUpdateHandler::ProcessHandler()
   std::string start_time = m_CTest->CurrentTime();
   double elapsed_time_start = cmSystemTools::GetTime();
 
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "* Update repository: " << command.c_str() << std::endl);
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "* Update repository: "
+    << command.c_str() << std::endl);
   if ( !m_CTest->GetShowOnly() )
     {
     command = "";
@@ -474,7 +508,8 @@ int cmCTestUpdateHandler::ProcessHandler()
           " " + extra_update_opts;
         ofs << "* Update repository: " << std::endl;
         ofs << "  Command: " << command.c_str() << std::endl;
-        bool res1 = m_CTest->RunCommand(command.c_str(), &partialOutput, &errors,
+        bool res1 = m_CTest->RunCommand(command.c_str(), &partialOutput,
+          &errors,
           &retVal, sourceDirectory, 0 /*m_TimeOut*/);
         ofs << "  Output: " << partialOutput.c_str() << std::endl;
         ofs << "  Errors: " << errors.c_str() << std::endl;
@@ -494,7 +529,7 @@ int cmCTestUpdateHandler::ProcessHandler()
     if ( ofs )
       {
       ofs << "--- Update repository ---" << std::endl;
-      ofs << goutput << std::endl;; 
+      ofs << goutput << std::endl;
       }
     }
   if ( !res || retVal )
@@ -514,27 +549,36 @@ int cmCTestUpdateHandler::ProcessHandler()
   os << "\t<StartDateTime>" << start_time << "</StartDateTime>\n"
     << "\t<UpdateCommand>" << m_CTest->MakeXMLSafe(command)
     << "</UpdateCommand>\n"
-    << "\t<UpdateType>" << m_CTest->MakeXMLSafe(cmCTestUpdateHandlerUpdateToString(updateType))
+    << "\t<UpdateType>" << m_CTest->MakeXMLSafe(
+      cmCTestUpdateHandlerUpdateToString(updateType))
     << "</UpdateType>\n";
 
-  // Even though it failed, we may have some useful information. Try to continue...
+  // Even though it failed, we may have some useful information. Try to
+  // continue...
   std::vector<cmStdString> lines;
   cmSystemTools::Split(goutput.c_str(), lines);
   std::vector<cmStdString> errLines;
   cmSystemTools::Split(errors.c_str(), errLines);
   lines.insert(lines.end(), errLines.begin(), errLines.end());
 
   // CVS style regular expressions
-  cmsys::RegularExpression cvs_date_author_regex("^date: +([^;]+); +author: +([^;]+); +state: +[^;]+;");
+  cmsys::RegularExpression cvs_date_author_regex(
+    "^date: +([^;]+); +author: +([^;]+); +state: +[^;]+;");
   cmsys::RegularExpression cvs_revision_regex("^revision +([^ ]*) *$");
-  cmsys::RegularExpression cvs_end_of_file_regex("^=============================================================================$");
-  cmsys::RegularExpression cvs_end_of_comment_regex("^----------------------------$");
+  cmsys::RegularExpression cvs_end_of_file_regex(
+    "^=========================================="
+    "===================================$");
+  cmsys::RegularExpression cvs_end_of_comment_regex(
+    "^----------------------------$");
 
   // Subversion style regular expressions
-  cmsys::RegularExpression svn_status_line_regex("^ *([0-9]+)  *([0-9]+)  *([^ ]+)  *([^ ][^\t\r\n]*)[ \t\r\n]*$");
-  cmsys::RegularExpression svn_latest_revision_regex("(Updated to|At) revision ([0-9]+)\\.");
+  cmsys::RegularExpression svn_status_line_regex(
+    "^ *([0-9]+)  *([0-9]+)  *([^ ]+)  *([^ ][^\t\r\n]*)[ \t\r\n]*$");
+  cmsys::RegularExpression svn_latest_revision_regex(
+    "(Updated to|At) revision ([0-9]+)\\.");
 
-  cmsys::RegularExpression file_removed_line("cvs update: `(.*)' is no longer in the repository");
+  cmsys::RegularExpression file_removed_line(
+    "cvs update: `(.*)' is no longer in the repository");
   cmsys::RegularExpression file_update_line("([A-Z])  *(.*)");
   std::string current_path = "<no-path>";
   bool first_file = true;
@@ -546,28 +590,35 @@ int cmCTestUpdateHandler::ProcessHandler()
   // In subversion, get the latest revision
   if ( updateType == cmCTestUpdateHandler::e_SVN )
     {
-    for ( cc= 0 ; cc < lines.size(); cc ++ )
+    for ( cc= 0; cc < lines.size(); cc ++ )
       {
       const char* line = lines[cc].c_str();
       if ( svn_latest_revision_regex.find(line) )
         {
-        svn_latest_revision = atoi(svn_latest_revision_regex.match(2).c_str());
+        svn_latest_revision = atoi(
+          svn_latest_revision_regex.match(2).c_str());
         }
       }
     if ( svn_latest_revision <= 0 )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem determining the current revision of the repository from output:" << std::endl << goutput.c_str() << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem determining the current "
+        "revision of the repository from output:" << std::endl
+        << goutput.c_str() << std::endl);
       }
     else
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Current revision of repository is: " << svn_latest_revision << std::endl);
+      cmCTestLog(m_CTest, HANDLER_OUTPUT,
+        "   Current revision of repository is: " << svn_latest_revision
+        << std::endl);
       }
     }
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Gathering version information (each . represents one updated file):" << std::endl);
+  cmCTestLog(m_CTest, HANDLER_OUTPUT,
+    "   Gathering version information (each . represents one updated file):"
+    << std::endl);
   int file_count = 0;
   std::string removed_line;
-  for ( cc= 0 ; cc < lines.size(); cc ++ )
+  for ( cc= 0; cc < lines.size(); cc ++ )
     {
     const char* line = lines[cc].c_str();
     if ( file_removed_line.find(line) )
@@ -596,7 +647,8 @@ int cmCTestUpdateHandler::ProcessHandler()
         modifiedOrConflict = true;
         }
       const char* file = upFile.c_str();
-      cmCTestLog(m_CTest, DEBUG, "Line" << cc << ": " << mod << " - " << file << std::endl);
+      cmCTestLog(m_CTest, DEBUG, "Line" << cc << ": " << mod << " - "
+        << file << std::endl);
 
       std::string output;
       if ( modifiedOrConflict )
@@ -608,22 +660,27 @@ int cmCTestUpdateHandler::ProcessHandler()
           logcommand = updateCommand + " -z3 log -N \"" + file + "\"";
           break;
         case cmCTestUpdateHandler::e_SVN:
-          if ( svn_latest_revision > 0 && svn_latest_revision > svn_current_revision )
+          if ( svn_latest_revision > 0 &&
+            svn_latest_revision > svn_current_revision )
             {
             cmOStringStream logCommandStream;
-            logCommandStream << updateCommand << " log -r " << svn_current_revision << ":" << svn_latest_revision
+            logCommandStream << updateCommand << " log -r "
+              << svn_current_revision << ":" << svn_latest_revision
               << " --xml \"" << file << "\"";
             logcommand = logCommandStream.str();
             }
           else
             {
-            logcommand = updateCommand + " status  --verbose \"" + file + "\"";
+            logcommand = updateCommand +
+              " status  --verbose \"" + file + "\"";
             svn_use_status = 1;
             }
           break;
           }
         cmCTestLog(m_CTest, DEBUG, "Do log: " << logcommand << std::endl);
-        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "* Get file update information: " << logcommand.c_str() << std::endl);
+        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+          "* Get file update information: " << logcommand.c_str()
+          << std::endl);
         ofs << "* Get log information for file: " << file << std::endl;
         ofs << "  Command: " << logcommand.c_str() << std::endl;
         res = m_CTest->RunCommand(logcommand.c_str(), &output, &errors,
@@ -669,7 +726,8 @@ int cmCTestUpdateHandler::ProcessHandler()
                 srevision2 = cvs_revision_regex.match(1);
                 }
               }
-            else if ( !have_second && !sline && cvs_date_author_regex.find(clp) )
+            else if ( !have_second && !sline &&
+              cvs_date_author_regex.find(clp) )
               {
               sline = kk + 1;
               if ( !have_first )
@@ -683,7 +741,8 @@ int cmCTestUpdateHandler::ProcessHandler()
                 sauthor2 = cvs_date_author_regex.match(2);
                 }
               }
-            else if ( sline && cvs_end_of_comment_regex.find(clp) || cvs_end_of_file_regex.find(clp))
+            else if ( sline && cvs_end_of_comment_regex.find(clp) ||
+              cvs_end_of_file_regex.find(clp))
               {
               if ( !have_first )
                 {
@@ -719,16 +778,24 @@ int cmCTestUpdateHandler::ProcessHandler()
             srevision1 = str.str();
             if (!svn_status_line_regex.find(output))
               {
-              cmCTestLog(m_CTest, ERROR_MESSAGE, "Bad output from SVN status command: " << output << std::endl);
+              cmCTestLog(m_CTest, ERROR_MESSAGE,
+                "Bad output from SVN status command: " << output
+                << std::endl);
               }
             else if ( svn_status_line_regex.match(4) != file )
               {
-              cmCTestLog(m_CTest, ERROR_MESSAGE, "Bad output from SVN status command. The file name returned: \"" << svn_status_line_regex.match(4) << "\" was different than the file specified: \"" << file << "\"" << std::endl);
+              cmCTestLog(m_CTest, ERROR_MESSAGE,
+                "Bad output from SVN status command. "
+                "The file name returned: \""
+                << svn_status_line_regex.match(4)
+                << "\" was different than the file specified: \"" << file
+                << "\"" << std::endl);
               }
             else
               {
               srevision1 = svn_status_line_regex.match(2);
-              int latest_revision = atoi(svn_status_line_regex.match(2).c_str());
+              int latest_revision = atoi(
+                svn_status_line_regex.match(2).c_str());
               if ( svn_current_revision < latest_revision )
                 {
                 srevision2 = str.str();
@@ -743,7 +810,8 @@ int cmCTestUpdateHandler::ProcessHandler()
               {
               int minrev = parser.GetMinRevision();
               int maxrev = parser.GetMaxRevision();
-              cmCTestUpdateHandlerSVNXMLParser::t_VectorOfCommits::iterator it;
+              cmCTestUpdateHandlerSVNXMLParser::
+                t_VectorOfCommits::iterator it;
               for ( it = parser.GetCommits()->begin(); 
                 it != parser.GetCommits()->end(); 
                 ++ it )
@@ -823,14 +891,18 @@ int cmCTestUpdateHandler::ProcessHandler()
           {
           srevision2 = srevision1;
           }
-        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "File: " << path.c_str() << " / " << fname.c_str() << " was updated by "
+        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "File: " << path.c_str()
+          << " / " << fname.c_str() << " was updated by "
           << sauthor1.c_str() << " to revision: " << srevision1.c_str()
           << " from revision: " << srevision2.c_str() << std::endl);
-        os << "\t\t<File Directory=\"" << cmCTest::MakeXMLSafe(path) << "\">" << cmCTest::MakeXMLSafe(fname)
+        os << "\t\t<File Directory=\"" << cmCTest::MakeXMLSafe(path) << "\">"
+          << cmCTest::MakeXMLSafe(fname)
           << "</File>\n"
-          << "\t\t<Directory>" << cmCTest::MakeXMLSafe(path) << "</Directory>\n"
+          << "\t\t<Directory>" << cmCTest::MakeXMLSafe(path)
+          << "</Directory>\n"
           << "\t\t<FullName>" << cmCTest::MakeXMLSafe(file) << "</FullName>\n"
-          << "\t\t<CheckinDate>" << cmCTest::MakeXMLSafe(sdate1) << "</CheckinDate>\n"
+          << "\t\t<CheckinDate>" << cmCTest::MakeXMLSafe(sdate1)
+          << "</CheckinDate>\n"
           << "\t\t<Author>" << cmCTest::MakeXMLSafe(sauthor1) << "</Author>\n"
           << "\t\t<Email>" << cmCTest::MakeXMLSafe(semail1) << "</Email>\n"
           << "\t\t<Log>" << cmCTest::MakeXMLSafe(comment1) << "</Log>\n"
@@ -842,19 +914,29 @@ int cmCTestUpdateHandler::ProcessHandler()
           os
             << "\t\t<Revisions>\n"
             << "\t\t\t<Revision>" << srevision1 << "</Revision>\n"
-            << "\t\t\t<PreviousRevision>" << srevision2 << "</PreviousRevision>\n"
-            << "\t\t\t<Author>" << cmCTest::MakeXMLSafe(sauthor1) << "</Author>\n"
-            << "\t\t\t<Date>" << cmCTest::MakeXMLSafe(sdate1) << "</Date>\n"
-            << "\t\t\t<Comment>" << cmCTest::MakeXMLSafe(comment1) << "</Comment>\n"
-            << "\t\t\t<Email>" << cmCTest::MakeXMLSafe(semail1) << "</Email>\n"
+            << "\t\t\t<PreviousRevision>" << srevision2
+            << "</PreviousRevision>\n"
+            << "\t\t\t<Author>" << cmCTest::MakeXMLSafe(sauthor1)
+            << "</Author>\n"
+            << "\t\t\t<Date>" << cmCTest::MakeXMLSafe(sdate1)
+            << "</Date>\n"
+            << "\t\t\t<Comment>" << cmCTest::MakeXMLSafe(comment1)
+            << "</Comment>\n"
+            << "\t\t\t<Email>" << cmCTest::MakeXMLSafe(semail1)
+            << "</Email>\n"
             << "\t\t</Revisions>\n"
             << "\t\t<Revisions>\n"
             << "\t\t\t<Revision>" << srevision2 << "</Revision>\n"
-            << "\t\t\t<PreviousRevision>" << srevision2 << "</PreviousRevision>\n"
-            << "\t\t\t<Author>" << cmCTest::MakeXMLSafe(sauthor2) << "</Author>\n"
-            << "\t\t\t<Date>" << cmCTest::MakeXMLSafe(sdate2) << "</Date>\n"
-            << "\t\t\t<Comment>" << cmCTest::MakeXMLSafe(comment2) << "</Comment>\n"
-            << "\t\t\t<Email>" << cmCTest::MakeXMLSafe(semail2) << "</Email>\n"
+            << "\t\t\t<PreviousRevision>" << srevision2
+            << "</PreviousRevision>\n"
+            << "\t\t\t<Author>" << cmCTest::MakeXMLSafe(sauthor2)
+            << "</Author>\n"
+            << "\t\t\t<Date>" << cmCTest::MakeXMLSafe(sdate2)
+            << "</Date>\n"
+            << "\t\t\t<Comment>" << cmCTest::MakeXMLSafe(comment2)
+            << "</Comment>\n"
+            << "\t\t\t<Email>" << cmCTest::MakeXMLSafe(semail2)
+            << "</Email>\n"
             << "\t\t</Revisions>" << std::endl;
           }
         if ( mod == 'C' )
@@ -890,21 +972,25 @@ int cmCTestUpdateHandler::ProcessHandler()
     }
   if ( num_updated )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_updated << " updated files" << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_updated
+      << " updated files" << std::endl);
     }
   if ( num_modified )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_modified << " locally modified files" 
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_modified
+      << " locally modified files" 
       << std::endl);
     }
   if ( num_conflicting )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_conflicting << " conflicting files" 
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Found " << num_conflicting
+      << " conflicting files" 
       << std::endl);
     }
   if ( num_modified == 0 && num_conflicting == 0 && num_updated == 0 )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Project is up-to-date" << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Project is up-to-date"
+      << std::endl);
     }
   if ( !first_file )
     {
@@ -936,21 +1022,26 @@ int cmCTestUpdateHandler::ProcessHandler()
     << "\t<UpdateReturnStatus>";
   if ( num_modified > 0 || num_conflicting > 0 )
     {
-    os << "Update error: There are modified or conflicting files in the repository";
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "   There are modified or conflicting files in the repository" << std::endl);
+    os << "Update error: There are modified or conflicting files in the "
+      "repository";
+    cmCTestLog(m_CTest, ERROR_MESSAGE,
+      "   There are modified or conflicting files in the repository"
+      << std::endl);
     }
   if ( updateProducedError )
     {
     os << "Update error: ";
     os << m_CTest->MakeXMLSafe(checkoutErrorMessages);
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "   Update with command: " << command << " failed" << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE, "   Update with command: " << command
+      << " failed" << std::endl);
     }
   os << "</UpdateReturnStatus>" << std::endl;
   os << "</Update>" << std::endl;
 
   if (! res || retVal )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Error(s) when updating the project" << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE, "Error(s) when updating the project"
+      << std::endl);
     cmCTestLog(m_CTest, ERROR_MESSAGE, "Output: " << goutput << std::endl);
     return -1;
     }