              default:

                fprintf(stderr,"Other");

                cres.m_Status = cmCTest::OTHER_FAULT;

              }

            fprintf(stderr,"\n");

            }

          else if ( res == cmsysProcess_State_Error )

            {

            fprintf(stderr,"***Bad command\n");

            cres.m_Status = cmCTest::BAD_COMMAND;

            }

          else

            {

            fprintf(stderr,"***Failed\n");

            }

          failed.push_back(args[0].Value);

          }

        if (output != "")

          {

          if (dartStuff.find(output.c_str()))

            {

            std::string dartString = dartStuff.match(1);

            cmSystemTools::ReplaceString(output, dartString.c_str(),"");

            cres.m_RegressionImages = this->GenerateRegressionImages(dartString);

            }

          }

        }

      cres.m_Output = output;

      cres.m_ReturnValue = retVal;

      std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();

      if ( nwd.size() > m_ToplevelPath.size() )

        {

        nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);

        }

      cmSystemTools::ReplaceString(nwd, "\\", "/");

      cres.m_Path = nwd;

      cres.m_CompletionStatus = "Completed";

      m_TestResults.push_back( cres );

      }

    }

}

