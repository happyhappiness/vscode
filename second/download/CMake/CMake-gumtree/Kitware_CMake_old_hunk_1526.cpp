      int seconds = static_cast<int>(ttime) % 60;

      char buffer[100];

      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);

      *m_LogFile 

        << "----------------------------------------------------------"

        << std::endl

        << "\"" << testname.c_str() << "\" end time: " 

        << m_CTest->CurrentTime() << std::endl

        << "\"" << testname.c_str() << "\" time elapsed: " 

        << buffer << std::endl

        << "----------------------------------------------------------"

        << std::endl << std::endl;

