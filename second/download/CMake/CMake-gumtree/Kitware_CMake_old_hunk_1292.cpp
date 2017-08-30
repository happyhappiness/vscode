      {

      for(std::vector<std::string>::iterator l = p.Labels.begin();

          l !=  p.Labels.end(); ++l)

        {

        labelTimes[*l] += result.ExecutionTime;

        }

      }

    }

  // now print times

  for(std::set<cmStdString>::const_iterator i = labels.begin();

      i != labels.end(); ++i)

    {

    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTime in "

               << *i << " = " << labelTimes[*i] << " sec" );

    if ( this->LogFile )

        {

        *this->LogFile << "\nTime in " << *i << " = "

                       << labelTimes[*i] << " sec"  << std::endl;

        }

    }

}



//----------------------------------------------------------------------
