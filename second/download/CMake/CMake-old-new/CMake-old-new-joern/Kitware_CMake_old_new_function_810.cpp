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

  std::cout << (m_MemCheck ? "Memory check" : "Test") << " project" << std::endl;
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
      std::cerr << "No tests were found!!!\n";
      }
    }
  else
    {
    if (m_Verbose && passed.size() && 
      (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
      {
      std::cerr << "\nThe following tests passed:\n";
      for(std::vector<cmStdString>::iterator j = passed.begin();
          j != passed.end(); ++j)
        {   
        std::cerr << "\t" << *j << "\n";
        }
      }

    float percent = float(passed.size()) * 100.0f / total;
    if ( failed.size() > 0 &&  percent > 99)
      {
      percent = 99;
      }
    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
      percent, int(failed.size()), total);

    if (failed.size()) 
      {
      cmGeneratedFileStream ofs;

      std::cerr << "\nThe following tests FAILED:\n";
      m_CTest->OpenOutputFile("Temporary", "LastTestsFailed.log", ofs);

      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
      for(ftit = m_TestResults.begin();
        ftit != m_TestResults.end(); ++ftit)
        {
        if ( ftit->m_Status != cmCTestTestHandler::COMPLETED )
          {
          ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
          fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),
            this->GetTestStatus(ftit->m_Status));
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
      std::cerr << "Cannot create " << (m_MemCheck ? "memory check" : "testing")
        << " XML file" << std::endl;
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