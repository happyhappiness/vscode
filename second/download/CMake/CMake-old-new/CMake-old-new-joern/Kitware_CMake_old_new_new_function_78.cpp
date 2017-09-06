void cmCTestTestHandler::PrintSubprojectSummary()
{
  std::vector<std::string> subprojects =
    this->CTest->GetLabelsForSubprojects();

  cmCTestTestHandler::ListOfTests::iterator it = this->TestList.begin();
  std::map<std::string, double> labelTimes;
  std::map<std::string, int> labelCounts;
  std::set<std::string> labels;
  // initialize maps
  std::string::size_type maxlen = 0;
  for (; it != this->TestList.end(); ++it) {
    cmCTestTestProperties& p = *it;
    for (std::vector<std::string>::iterator l = p.Labels.begin();
         l != p.Labels.end(); ++l) {
      std::vector<std::string>::iterator subproject =
        std::find(subprojects.begin(), subprojects.end(), *l);
      if (subproject != subprojects.end()) {
        if ((*l).size() > maxlen) {
          maxlen = (*l).size();
        }
        labels.insert(*l);
        labelTimes[*l] = 0;
        labelCounts[*l] = 0;
      }
    }
  }
  cmCTestTestHandler::TestResultsVector::iterator ri =
    this->TestResults.begin();
  // fill maps
  for (; ri != this->TestResults.end(); ++ri) {
    cmCTestTestResult& result = *ri;
    cmCTestTestProperties& p = *result.Properties;
    for (std::vector<std::string>::iterator l = p.Labels.begin();
         l != p.Labels.end(); ++l) {
      std::vector<std::string>::iterator subproject =
        std::find(subprojects.begin(), subprojects.end(), *l);
      if (subproject != subprojects.end()) {
        labelTimes[*l] += result.ExecutionTime;
        ++labelCounts[*l];
      }
    }
  }
  // now print times
  if (!labels.empty()) {
    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
                       "\nSubproject Time Summary:", this->Quiet);
  }
  for (std::set<std::string>::const_iterator i = labels.begin();
       i != labels.end(); ++i) {
    std::string label = *i;
    label.resize(maxlen + 3, ' ');

    char buf[1024];
    sprintf(buf, "%6.2f sec", labelTimes[*i]);

    std::ostringstream labelCountStr;
    labelCountStr << "(" << labelCounts[*i] << " test";
    if (labelCounts[*i] > 1) {
      labelCountStr << "s";
    }
    labelCountStr << ")";

    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "\n"
                         << label << " = " << buf << " "
                         << labelCountStr.str(),
                       this->Quiet);
    if (this->LogFile) {
      *this->LogFile << "\n" << *i << " = " << buf << "\n";
    }
  }
  if (!labels.empty()) {
    if (this->LogFile) {
      *this->LogFile << "\n";
    }
    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "\n", this->Quiet);
  }
}