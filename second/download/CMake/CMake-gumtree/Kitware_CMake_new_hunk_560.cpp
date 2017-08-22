    label.resize(maxlen +3, ' ');
    char buf[1024];
    sprintf(buf, "%6.2f sec", labelTimes[*i]);
    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "\n"
               << label << " = " << buf, this->Quiet );
    if ( this->LogFile )
      {
      *this->LogFile << "\n" << *i << " = "
