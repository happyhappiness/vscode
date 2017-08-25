{
  time_t tctime = time(0);
  struct tm *lctime = gmtime(&tctime);
  char datestring[100];
  sprintf(datestring, "%4d%02d%02d-%d%d",
          lctime->tm_year + 1900,
          lctime->tm_mon,
          lctime->tm_mday,
          lctime->tm_hour,
          lctime->tm_min);

  os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
     << "\" BuildStamp=\"" << datestring << "-Experimental\" Name=\""
     << m_DartConfiguration["Site"] << "\">\n"
     << "<Build>\n"
     << "  <StartDateTime>" << ::CurrentTime() << "</StartDateTime>\n"
     << "  <BuildCommand>" << m_DartConfiguration["MakeCommand"]
     << "</BuildCommand>" << std::endl;
    
  std::vector<cmCTestBuildErrorWarning>::iterator it;
  for ( it = ew.begin(); it != ew.end(); it++ )
    {
    cmCTestBuildErrorWarning *cm = &(*it);
    os << "  <" << (cm->m_Error ? "Error" : "Warning") << ">\n"
       << "    <BuildLogLine>" << cm->m_LogLine << "</BuildLogLine>\n"
       << "    <Text>" << cm->m_Text << "</Text>" << std::endl;
    if ( cm->m_SourceFile.size() > 0 )
      {
      os << "    <SourceFile>" << cm->m_SourceFile << "</SourceFile>" 
         << std::endl;
      }
    if ( cm->m_SourceFileTail.size() > 0 )
      {
      os << "    <SourceFileTail>" << cm->m_SourceFileTail 
         << "</SourceFileTail>" << std::endl;
      }
    if ( cm->m_LineNumber >= 0 )
      {
      os << "    <SourceLineNumber>" << cm->m_LineNumber 
         << "</SourceLineNumber>" << std::endl;
      }
    os << "    <PreContext>" << cm->m_PreContext << "</PreContext>\n"
       << "    <PostContext>" << cm->m_PostContext << "</PostContext>\n"
       << "  </" << (cm->m_Error ? "Error" : "Warning") << ">" 
       << std::endl;
    }
  os << "  <Log Encoding=\"base64\" Compression=\"/bin/gzip\">\n    </Log>\n"
     << "  <EndDateTime>" << ::CurrentTime() << "</EndDateTime>\n"
     << "</Build>\n"
     << "</Site>" << std::endl;
}