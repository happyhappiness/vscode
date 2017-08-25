{
    double ttime = clock_finish - clock_start;
    int hours = static_cast<int>(ttime / (60 * 60));
    int minutes = static_cast<int>(ttime / 60) % 60;
    int seconds = static_cast<int>(ttime) % 60;
    char buffer[100];
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
    *this->LogFile
      << "----------------------------------------------------------"
      << std::endl
      << "\"" << testname.c_str() << "\" end time: "
      << this->CTest->CurrentTime() << std::endl
      << "\"" << testname.c_str() << "\" time elapsed: "
      << buffer << std::endl
      << "----------------------------------------------------------"
      << std::endl << std::endl;
    }