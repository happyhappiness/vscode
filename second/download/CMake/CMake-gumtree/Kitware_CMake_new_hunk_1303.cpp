    char buf[1024];
    sprintf(buf, "%6.2f sec", cres.ExecutionTime);
    cmCTestLog(this->CTest, HANDLER_OUTPUT, buf << "\n" );
    if ( this->LogFile )
      {
      *this->LogFile << "\nTest time = " << buf << std::endl;
      }
    if (!output.empty() && output.find("<DartMeasurement") != output.npos)
      {
      if (this->DartStuff.find(output.c_str()))