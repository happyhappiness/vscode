int cmCTestTestHandler::ProcessHandler()
{
  // Update internal data structure from generic one
  this->SetTestsToRunInformation(this->GetOption("TestsToRunInformation"));
  this->SetUseUnion(cmSystemTools::IsOn(this->GetOption("UseUnion"))); 
  if(this->GetOption("ParallelLevel"))
    {
    this->CTest->SetParallelLevel(atoi(this->GetOption("ParallelLevel")));
    }
  const char* val;
  val = this->GetOption("LabelRegularExpression");
  if ( val )
    {
    this->UseIncludeLabelRegExpFlag = true;
    this->IncludeLabelRegExp = val;
    }
  val = this->GetOption("ExcludeLabelRegularExpression");
  if ( val )
    {
    this->UseExcludeLabelRegExpFlag = true;
    this->ExcludeLabelRegularExpression = val;
    }
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
  
  this->TestResults.clear();

  cmCTestLog(this->CTest, HANDLER_OUTPUT,
             (this->MemCheck ? "Memory check" : "Test")
             << " project " << cmSystemTools::GetCurrentWorkingDirectory()
             << std::endl);
  if ( ! this->PreProcessHandler() )
    {
    return -1;
    }

  cmGeneratedFileStream mLogFile;
  this->StartLogFile((this->MemCheck ? "DynamicAnalysis" : "Test"), mLogFile);
  this->LogFile = &mLogFile;

  std::vector<cmStdString> passed;
  std::vector<cmStdString> failed;
  int total;

  //start the real time clock
  double clock_start, clock_finish;
  clock_start = cmSystemTools::GetTime();

  this->ProcessDirectory(passed, failed);

  clock_finish = cmSystemTools::GetTime();

  total = int(passed.size()) + int(failed.size());

  if (total == 0)
    {
    if ( !this->CTest->GetShowOnly() )
      {
      cmCTestLog(this->CTest, ERROR_MESSAGE, "No tests were found!!!"
        << std::endl);
      }
    }
  else
    {
    if (this->HandlerVerbose && passed.size() &&
      (this->UseIncludeRegExpFlag || this->UseExcludeRegExpFlag))
      {
      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
        << "The following tests passed:" << std::endl);
      for(std::vector<cmStdString>::iterator j = passed.begin();
          j != passed.end(); ++j)
        {
        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "\t" << *j
          << std::endl);
        }
      }

    float percent = float(passed.size()) * 100.0f / total;
    if ( failed.size() > 0 &&  percent > 99)
      {
      percent = 99;
      }
    
    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
               << static_cast<int>(percent + .5) << "% tests passed, "
               << failed.size() << " tests failed out of " 
               << total << std::endl); 
    double totalTestTime = 0;

    for(cmCTestTestHandler::TestResultsVector::size_type cc = 0;
        cc < this->TestResults.size(); cc ++ )
      {
      cmCTestTestResult *result = &this->TestResults[cc];
      totalTestTime += result->ExecutionTime;
      }
    
    char realBuf[1024];
    sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
               << realBuf << "\n" );

    char totalBuf[1024];
    sprintf(totalBuf, "%6.2f sec", totalTestTime); 
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (parallel) = "
               <<  totalBuf << "\n" );

    if (failed.size())
      {
      cmGeneratedFileStream ofs;
      cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
                 << "The following tests FAILED:" << std::endl);
      this->StartLogFile("TestsFailed", ofs);
      
      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
      for(ftit = this->TestResults.begin();
          ftit != this->TestResults.end(); ++ftit)
        {
        if ( ftit->Status != cmCTestTestHandler::COMPLETED )
          {
          ofs << ftit->TestCount << ":" << ftit->Name << std::endl;
          cmCTestLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
                     << ftit->TestCount << " - " 
                     << ftit->Name.c_str() << " ("
                     << this->GetTestStatus(ftit->Status) << ")" 
                     << std::endl);
          }
        }
      }
    }

  if ( this->CTest->GetProduceXML() )
    {
    cmGeneratedFileStream xmlfile;
    if( !this->StartResultingXML(
          (this->MemCheck ? cmCTest::PartMemCheck : cmCTest::PartTest),
        (this->MemCheck ? "DynamicAnalysis" : "Test"), xmlfile) )
      {
      cmCTestLog(this->CTest, ERROR_MESSAGE, "Cannot create "
        << (this->MemCheck ? "memory check" : "testing")
        << " XML file" << std::endl);
      this->LogFile = 0;
      return 1;
      }
    this->GenerateDartOutput(xmlfile);
    }

  if ( ! this->PostProcessHandler() )
    {
    this->LogFile = 0;
    return -1;
    }

  if ( !failed.empty() )
    {
    this->LogFile = 0;
    return -1;
    }
  this->LogFile = 0;
  return 0;
}