                cres.m_Status = cmCTest::SEGFAULT;
                break;
              case cmsysProcess_Exception_Illegal:
                fprintf(stderr,"SegFault");
                cres.m_Status = cmCTest::ILLEGAL;
                break;
              case cmsysProcess_Exception_Interrupt:
                fprintf(stderr,"SegFault");
                cres.m_Status = cmCTest::INTERRUPT;
                break;
              case cmsysProcess_Exception_Numerical:
                fprintf(stderr,"SegFault");
                cres.m_Status = cmCTest::NUMERICAL;
                break;
              default:
