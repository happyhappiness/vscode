      }

    if ( tag.size() == 0 )

      {

#ifdef HAVE_CURL

      if ( m_TestModel == cmCTest::NIGHTLY )

        {

        int hour;

        int min;

        int sec;

        char stz[100];

        int tz;

        tctime = time(0);

        //Convert the nightly start time to seconds. Since we are

        //providing only a time and a timezone, the current date of

        //the local machine is assumed. Consequently, nightlySeconds

        //is the time at which the nightly dashboard was opened or

        //will be opened on the date of the current client machine.

        //As such, this time may be in the past or in the future.

        time_t ntime = curl_getdate(

          m_DartConfiguration["NightlyStartTime"].c_str(), 

          &tctime);

        tctime = time(0);

        std::cout << "Seconds: " << tctime << std::endl;

        if ( ntime > tctime )

          {

          // If nightlySeconds is in the past, this is the current

          // open dashboard, then return nightlySeconds.  If

          // nightlySeconds is in the future, this is the next

          // dashboard to be opened, so subtract 24 hours to get the

          // time of the current open dashboard

          ntime -= (24 * 60 * 60 );

          std::cout << "Pick yesterday" << std::endl;

          }

        std::cout << "nightlySeconds: " << ntime << std::endl;

        lctime = gmtime(&ntime);

        }

#endif

      char datestring[100];

      sprintf(datestring, "%04d%02d%02d-%02d%02d",

              lctime->tm_year + 1900,

