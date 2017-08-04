      }
    char realBuf[1024];
    sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
               << realBuf << "\n" );

    if (!failed.empty())
      {
