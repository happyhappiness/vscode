        return 0;

        }

      }



    // Create new "TAG" file or read existing one:

    //

    bool createNewTag = true;

    if (command)

      {

      createNewTag = command->ShouldCreateNewTag();

      }



    std::string tagfile = testingDir + "/TAG";

    std::ifstream tfin(tagfile.c_str());

    std::string tag;



    if (createNewTag)

      {

      time_t tctime = time(0);

      if ( this->TomorrowTag )

        {

        tctime += ( 24 * 60 * 60 );

        }

      struct tm *lctime = gmtime(&tctime);

      if ( tfin && cmSystemTools::GetLineFromStream(tfin, tag) )

        {

        int year = 0;

        int mon = 0;

        int day = 0;

        int hour = 0;

        int min = 0;

        sscanf(tag.c_str(), "%04d%02d%02d-%02d%02d",

               &year, &mon, &day, &hour, &min);

        if ( year != lctime->tm_year + 1900 ||

             mon != lctime->tm_mon+1 ||

             day != lctime->tm_mday )

          {

          tag = "";

          }

        std::string tagmode;

        if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )

          {

          if (tagmode.size() > 4 && !this->Parts[PartStart])

            {

            this->TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());

            }

          }

        tfin.close();

        }

      if (tag.size() == 0 || (0 != command) || this->Parts[PartStart])

        {

        cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString()

          << std::endl);

        cmCTestLog(this, DEBUG, "TestModel: " << this->TestModel << std::endl);

        if ( this->TestModel == cmCTest::NIGHTLY )

          {

          lctime = this->GetNightlyTime(

            this->GetCTestConfiguration("NightlyStartTime"),

            this->TomorrowTag);

          }

        char datestring[100];

        sprintf(datestring, "%04d%02d%02d-%02d%02d",

                lctime->tm_year + 1900,

                lctime->tm_mon+1,

                lctime->tm_mday,

                lctime->tm_hour,

                lctime->tm_min);

        tag = datestring;

        std::ofstream ofs(tagfile.c_str());

        if ( ofs )

          {

          ofs << tag << std::endl;

          ofs << this->GetTestModelString() << std::endl;

          }

        ofs.close();

        if ( 0 == command )

          {

          cmCTestLog(this, OUTPUT, "Create new tag: " << tag << " - "

            << this->GetTestModelString() << std::endl);

          }

        }

      }

    else

      {

      if ( tfin )

        {

        cmSystemTools::GetLineFromStream(tfin, tag);

        tfin.close();

        }



      if ( tag.empty() )

        {

        cmCTestLog(this, ERROR_MESSAGE,

          "Cannot read existing TAG file in " << testingDir

          << std::endl);

        return 0;

        }



      cmCTestLog(this, OUTPUT, "  Use existing tag: " << tag << " - "

        << this->GetTestModelString() << std::endl);

      }



    this->CurrentTag = tag;

    }



  return 1;

}



//----------------------------------------------------------------------

bool cmCTest::InitializeFromCommand(cmCTestStartCommand* command)

{

  std::string src_dir

    = this->GetCTestConfiguration("SourceDirectory").c_str();

  std::string bld_dir = this->GetCTestConfiguration("BuildDirectory").c_str();

