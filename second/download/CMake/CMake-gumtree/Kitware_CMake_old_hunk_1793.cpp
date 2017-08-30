        errorwarning.m_PreContext += lines[jj] + "\n";

        }

      for ( jj = kk+1; 

            jj < lines.size() && jj < kk + 6 /* && markedLines[jj] == 0*/; 

            jj ++ )

        {

        errorwarning.m_PostContext += lines[jj] + "\n";

        }

      errorsWarnings.push_back(errorwarning);

      }

    }

  /*

  this->GenerateDartBuildOutput(std::cout, 

                                errorsWarnings);

  */

}





void ctest::GenerateDartBuildOutput(std::ostream& os, 

                                    std::vector<cmCTestBuildErrorWarning> ew)

{

  time_t tctime = time(0);

  struct tm *lctime = gmtime(&tctime);

  char datestring[100];

  sprintf(datestring, "%4d%02d%02d-%d%d",

          lctime->tm_year + 1900,

          lctime->tm_mon,

          lctime->tm_mday,

          lctime->tm_hour,

          lctime->tm_min);



  os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"

     << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]

     << "\" BuildStamp=\"" << datestring << "-Experimental\" Name=\""

     << m_DartConfiguration["Site"] << "\">\n"

     << "<Build>\n"

     << "  <StartDateTime>" << ::CurrentTime() << "</StartDateTime>\n"

     << "  <BuildCommand>" << m_DartConfiguration["MakeCommand"]

     << "</BuildCommand>" << std::endl;

    

