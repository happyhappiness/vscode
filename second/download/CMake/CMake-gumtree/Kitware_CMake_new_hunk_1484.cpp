      std::string tagmode;

      if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )

        {

        if ( tagmode.size() > 4 && !( this->Tests[cmCTest::START_TEST] ||

            this->Tests[ALL_TEST] ))

          {

          this->TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());

          }

        }

      tfin.close();

      }

    if ( tag.size() == 0 || new_tag || this->Tests[cmCTest::START_TEST] ||

      this->Tests[ALL_TEST])

      {

      cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString()

        << std::endl);

      cmCTestLog(this, DEBUG, "TestModel: " << this->TestModel << std::endl);

      if ( this->TestModel == cmCTest::NIGHTLY )

        {

        lctime = this->GetNightlyTime(

          this->GetCTestConfiguration("NightlyStartTime"), this->TomorrowTag);

        }

      char datestring[100];

      sprintf(datestring, "%04d%02d%02d-%02d%02d",

