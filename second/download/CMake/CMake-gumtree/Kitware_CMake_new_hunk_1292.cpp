      {

      for(std::vector<std::string>::iterator l = p.Labels.begin();

          l !=  p.Labels.end(); ++l)

        {  

        labelTimes[*l] += result.ExecutionTime;

        }

      }

    }

  // now print times  

  if(labels.size())

    {

    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nLabel Time Summary:");

    }

  for(std::set<cmStdString>::const_iterator i = labels.begin();

      i != labels.end(); ++i)

    {

    std::string label = *i;

    label.resize(maxlen +3, ' ');

    char buf[1024];

    sprintf(buf, "%6.2f sec", labelTimes[*i]);

    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\n"

               << label << " = " << buf );

    if ( this->LogFile )

      {

      *this->LogFile << "\n" << *i << " = "

                     << buf << "\n";

      }

    }

  if(labels.size())

    { 

    if(this->LogFile)

      {

      *this->LogFile << "\n";

      }

    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\n");

    }



}



//----------------------------------------------------------------------
