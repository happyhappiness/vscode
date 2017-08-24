void ctest::GenerateDartOutput(std::ostream& os)
{
  if ( !m_DartMode )
    {
    return;
    }

  if ( m_TestResults.size() == 0 )
    {
    return;
    }

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
     << "<Testing>\n"
     << "  <StartDateTime>" << ::CurrentTime() << "</StartDateTime>\n"
     << "  <TestList>\n";
  tm_TestResultsVector::size_type cc;
  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
    {
    cmCTestTestResult *result = &m_TestResults[cc];
    os << "    <Test>" << result->m_Path << "/" << result->m_Name 
       << "</Test>" << std::endl;
    }
  os << "  </TestList>\n";
  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
    {
    cmCTestTestResult *result = &m_TestResults[cc];
    os << "  <Test Status=\"" << (result->m_ReturnValue?"failed":"passed") 
       << "\">\n"
       << "    <Name>" << result->m_Name << "</Name>\n"
       << "    <Path>" << result->m_Path << "</Path>\n"
       << "    <FullName>" << result->m_Path << "/" << result->m_Name << "</FullName>\n"
       << "    <FullCommandLine>" << result->m_FullCommandLine << "</FullCommandLine>\n"
       << "    <Results>" << std::endl;
    if ( result->m_ReturnValue )
      {
      os << "      <NamedMeasurement type=\"text/string\" name=\"Exit Code\"><Value>"
         << "CHILDSTATUS" << "</Value></NamedMeasurement>\n"
         << "      <NamedMeasurement type=\"text/string\" name=\"Exit Value\"><Value>"
         << result->m_ReturnValue << "</Value></NamedMeasurement>" << std::endl;
      }
    os << "      <NamedMeasurement type=\"numeric/double\" "
       << "name=\"Execution Time\"><Value>"
       << result->m_ExecutionTime << "</Value></NamedMeasurement>\n"
       << "      <NamedMeasurement type=\"text/string\" "
       << "name=\"Completion Status\"><Value>"
       << result->m_CompletionStatus << "</Value></NamedMeasurement>\n"
       << "      <Measurement>\n"
       << "        <Value>" << result->m_Output << "</value>\n"
       << "      </Measurement>\n"
       << "    </Results>\n"
       << "  </Test>" << std::endl;
    }
  
  os << "<EndDateTime>" << ::CurrentTime() << "</EndDateTime>\n"
     << "</Testing>\n"
     << "</Site>" << std::endl;
}