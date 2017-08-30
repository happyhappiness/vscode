        cres.m_Status = cmCTest::FAILED;
        if ( res == cmsysProcess_State_Expired )
          {
          std::cerr << "***Timeout\n";
          cres.m_Status = cmCTest::TIMEOUT;
          }
        else if ( res == cmsysProcess_State_Exception )
          {
          std::cerr << "***Exception: ";
          switch ( retVal )
            {
          case cmsysProcess_Exception_Fault:
            std::cerr << "SegFault";
            cres.m_Status = cmCTest::SEGFAULT;
            break;
          case cmsysProcess_Exception_Illegal:
            std::cerr << "Illegal";
            cres.m_Status = cmCTest::ILLEGAL;
            break;
          case cmsysProcess_Exception_Interrupt:
            std::cerr << "Interrupt";
            cres.m_Status = cmCTest::INTERRUPT;
            break;
          case cmsysProcess_Exception_Numerical:
            std::cerr << "Numerical";
            cres.m_Status = cmCTest::NUMERICAL;
            break;
          default:
            std::cerr << "Other";
            cres.m_Status = cmCTest::OTHER_FAULT;
            }
           std::cerr << "\n";
          }
        else if ( res == cmsysProcess_State_Error )
          {
          std::cerr << "***Bad command " << res << "\n";
          cres.m_Status = cmCTest::BAD_COMMAND;
          }
        else
          {
          std::cerr << "***Failed\n";
          }
        failed.push_back(testname);
        }
