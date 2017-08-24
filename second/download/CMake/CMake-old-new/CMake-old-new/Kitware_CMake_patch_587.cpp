@@ -218,13 +218,13 @@ int cmCTestUpdateHandler::ProcessHandler()
   std::cout << "Updating the repository: " << sourceDirectory << std::endl;
 
   // Get update command
-  std::string updateCommand = m_CTest->GetDartConfiguration("UpdateCommand");
+  std::string updateCommand = m_CTest->GetCTestConfiguration("UpdateCommand");
   if ( updateCommand.empty() )
     {
-    updateCommand = m_CTest->GetDartConfiguration("CVSCommand");
+    updateCommand = m_CTest->GetCTestConfiguration("CVSCommand");
     if ( updateCommand.empty() )
       {
-      updateCommand = m_CTest->GetDartConfiguration("SVNCommand");
+      updateCommand = m_CTest->GetCTestConfiguration("SVNCommand");
       if ( updateCommand.empty() )
         {
         std::cerr << "Cannot find CVSCommand, SVNCommand, or UpdateCommand key in the DartConfiguration.tcl" << std::endl;
@@ -242,20 +242,20 @@ int cmCTestUpdateHandler::ProcessHandler()
     }
   else
     {
-    updateType = this->DetermineType(updateCommand.c_str(), m_CTest->GetDartConfiguration("UpdateType").c_str());
+    updateType = this->DetermineType(updateCommand.c_str(), m_CTest->GetCTestConfiguration("UpdateType").c_str());
     }
 
   // And update options
-  std::string updateOptions = m_CTest->GetDartConfiguration("UpdateOptions");
+  std::string updateOptions = m_CTest->GetCTestConfiguration("UpdateOptions");
   if ( updateOptions.empty() )
     {
     switch (updateType)
       {
     case cmCTestUpdateHandler::e_CVS:
-      updateOptions = m_CTest->GetDartConfiguration("CVSUpdateOptions");
+      updateOptions = m_CTest->GetCTestConfiguration("CVSUpdateOptions");
       break;
     case cmCTestUpdateHandler::e_SVN:
-      updateOptions = m_CTest->GetDartConfiguration("SVNUpdateOptions");
+      updateOptions = m_CTest->GetCTestConfiguration("SVNUpdateOptions");
       break;
       }
     }
@@ -264,7 +264,7 @@ int cmCTestUpdateHandler::ProcessHandler()
   std::string extra_update_opts;
   if ( m_CTest->GetTestModel() == cmCTest::NIGHTLY )
     {
-    struct tm* t = cmCTest::GetNightlyTime(m_CTest->GetDartConfiguration("NightlyStartTime"),
+    struct tm* t = cmCTest::GetNightlyTime(m_CTest->GetCTestConfiguration("NightlyStartTime"),
       m_Verbose, m_CTest->GetTomorrowTag());
     char current_time[1024];
     sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
@@ -418,8 +418,8 @@ int cmCTestUpdateHandler::ProcessHandler()
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     << "<Update mode=\"Client\" Generator=\"ctest-"
     << cmVersion::GetCMakeVersion() << "\">\n"
-    << "\t<Site>" << m_CTest->GetDartConfiguration("Site") << "</Site>\n"
-    << "\t<BuildName>" << m_CTest->GetDartConfiguration("BuildName")
+    << "\t<Site>" << m_CTest->GetCTestConfiguration("Site") << "</Site>\n"
+    << "\t<BuildName>" << m_CTest->GetCTestConfiguration("BuildName")
     << "</BuildName>\n"
     << "\t<BuildStamp>" << m_CTest->GetCurrentTag() << "-"
     << m_CTest->GetTestModelString() << "</BuildStamp>" << std::endl;