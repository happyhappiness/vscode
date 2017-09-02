int cmCTestTestHandler::ProcessHandler()
{
  // Update internal data structure from generic one
  this->SetTestsToRunInformation(this->GetOption("TestsToRunInformation"));
  this->SetUseUnion(cmSystemTools::IsOn(this->GetOption("UseUnion")));
  const char* val;
  val = this->GetOption("IncludeRegularExpression");
  if ( val )
    {
    this->UseIncludeRegExp();
    this->SetIncludeRegExp(val);
    }
  val = this->GetOption("ExcludeRegularExpression");
  if ( val )
    {
    this->UseExcludeRegExp();
    this->SetExcludeRegExp(val);
    }

  m_TestResults.clear();

  cmCTestLog(m_CTest, HANDLER_OUTPUT, (m_MemCheck ? "Memory check" : "Test") << " project" << std::endl);
  if ( ! this->PreProcessHandler() )
    {
    return -1;
    }

  std::vector<cmStdString> passed;
  std::vector<cmStdString> failed;
  int total;

  this->ProcessDirectory(passed, failed);

  total = int(passed.size()) + int(failed.size());

  if (total == 0)
    {
    if ( !m_CTest->GetShowOnly() )
      {
      cmCTestLog(m_CTest, ERROR, "No tests were found!!!" << std::endl);
      }
    }
  else
    {
    if (m_HandlerVerbose && passed.size() && 
      (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
      {
      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl << "The following tests passed:" << std::endl);
      for(std::vector<cmStdString>::iterator j = passed.begin();
          j != passed.end(); ++j)
        {   
        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "\t" << *j << std::endl);
        }
      }

    float percent = float(passed.size()) * 100.0f / total;
    if ( failed.size() > 0 &&  percent > 99)
      {
      percent = 99;
      }
    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl << std::setprecision(0) << percent << "% tests passed, "
      << failed.size() << " tests failed out of " << total << std::endl);
    //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
    //  percent, int(failed.size()), total);

    if (failed.size()) 
      {
      cmGeneratedFileStream ofs;

      cmCTestLog(m_CTest, ERROR, std::endl << "The following tests FAILED:" << std::endl);
      m_CTest->OpenOutputFile("Temporary", "LastTestsFailed.log", ofs);

      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
      for(ftit = m_TestResults.begin();
        ftit != m_TestResults.end(); ++ftit)
        {
        if ( ftit->m_Status != cmCTestTestHandler::COMPLETED )
          {
          ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
          cmCTestLog(m_CTest, HANDLER_OUTPUT, "\t" << std::setw(3) << ftit->m_TestCount << " - " << ftit->m_Name.c_str() << " (" << this->GetTestStatus(ftit->m_Status) << ")" << std::endl);
          //fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),
          //  this->GetTestStatus(ftit->m_Status));
          }
        }

      }
    }

  if ( m_CTest->GetProduceXML() )
    {
    cmGeneratedFileStream xmlfile;
    if( !m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
        (m_MemCheck ? "DynamicAnalysis.xml" : "Test.xml"), xmlfile, true) )
      {
      cmCTestLog(m_CTest, ERROR, "Cannot create " << (m_MemCheck ? "memory check" : "testing")
        << " XML file" << std::endl);
      return 1;
      }
    this->GenerateDartOutput(xmlfile);
    }

  if ( ! this->PostProcessHandler() )
    {
    return -1;
    }

  if ( !failed.empty() )
    {
    return -1;
    }
  return 0;
}