void cmCTestTestHandler::PrintLabelSummary()
{
  cmCTestTestHandler::ListOfTests::iterator it = this->TestList.begin();
  cmCTestTestHandler::TestResultsVector::iterator ri =
    this->TestResults.begin();
  std::map<cmStdString, double> labelTimes;
  std::set<cmStdString> labels;
  // initialize maps
  std::string::size_type maxlen = 0;
  for(; it != this->TestList.end(); ++it)
    {
    cmCTestTestProperties& p = *it;
    if(p.Labels.size() != 0)
      {
      for(std::vector<std::string>::iterator l = p.Labels.begin();
          l !=  p.Labels.end(); ++l)
        {
        if((*l).size() > maxlen)
          {
          maxlen = (*l).size();
          }
        labels.insert(*l);
        labelTimes[*l] = 0;
        }
      }
    }
  it = this->TestList.begin();
  ri = this->TestResults.begin();
  // fill maps
  for(; it != this->TestList.end(); ++it, ++ri)
    {
    cmCTestTestProperties& p = *it;
    cmCTestTestResult &result = *ri;
    if(p.Labels.size() != 0)
      {
      for(std::vector<std::string>::iterator l = p.Labels.begin();
          l !=  p.Labels.end(); ++l)
        {  
        labelTimes[*l] += result.ExecutionTime;
        }
      }
    }
  // now print times  
  if(labels.size())
    {
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nLabel Time Summary:");
    }
  for(std::set<cmStdString>::const_iterator i = labels.begin();
      i != labels.end(); ++i)
    {
    std::string label = *i;
    label.resize(maxlen +3, ' ');
    char buf[1024];
    sprintf(buf, "%6.2f sec", labelTimes[*i]);
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\n"
               << label << " = " << buf );
    if ( this->LogFile )
      {
      *this->LogFile << "\n" << *i << " = "
                     << buf << "\n";
      }
    }
  if(labels.size())
    { 
    if(this->LogFile)
      {
      *this->LogFile << "\n";
      }
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\n");
    }

}