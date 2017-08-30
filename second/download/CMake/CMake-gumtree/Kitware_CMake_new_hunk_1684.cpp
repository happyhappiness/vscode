                cres.m_Status = cmCTest::SEGFAULT;

                break;

              case cmsysProcess_Exception_Illegal:

                fprintf(stderr,"Illegal");

                cres.m_Status = cmCTest::ILLEGAL;

                break;

              case cmsysProcess_Exception_Interrupt:

                fprintf(stderr,"Interrupt");

                cres.m_Status = cmCTest::INTERRUPT;

                break;

              case cmsysProcess_Exception_Numerical:

                fprintf(stderr,"Numerical");

                cres.m_Status = cmCTest::NUMERICAL;

                break;

              default:

