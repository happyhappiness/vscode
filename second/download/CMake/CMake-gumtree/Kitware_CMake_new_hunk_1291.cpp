               << static_cast<int>(percent + .5) << "% tests passed, "
               << failed.size() << " tests failed out of " 
               << total << std::endl); 
    if(this->CTest->GetLabelSummary())
      {
      this->PrintLabelSummary();
      }
    char realBuf[1024];
    sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
               << realBuf << "\n" );

    if (failed.size())
      {
      cmGeneratedFileStream ofs;
