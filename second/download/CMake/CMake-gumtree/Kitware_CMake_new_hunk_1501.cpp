  const char* minInterval;

  const char* contDuration;



  this->SourceDir

    = this->Makefile->GetSafeDefinition("CTEST_SOURCE_DIRECTORY");

  this->BinaryDir

    = this->Makefile->GetSafeDefinition("CTEST_BINARY_DIRECTORY");

  this->CTestCmd

    = this->Makefile->GetSafeDefinition("CTEST_COMMAND");

  this->CVSCheckOut

    = this->Makefile->GetSafeDefinition("CTEST_CVS_CHECKOUT");

  this->CTestRoot

    = this->Makefile->GetSafeDefinition("CTEST_DASHBOARD_ROOT");

  this->CVSCmd

    = this->Makefile->GetSafeDefinition("CTEST_CVS_COMMAND");

  this->CTestEnv

    = this->Makefile->GetSafeDefinition("CTEST_ENVIRONMENT");

  this->InitCache

    = this->Makefile->GetSafeDefinition("CTEST_INITIAL_CACHE");

  this->CMakeCmd

    = this->Makefile->GetSafeDefinition("CTEST_CMAKE_COMMAND");

  this->CMOutFile

    = this->Makefile->GetSafeDefinition("CTEST_CMAKE_OUTPUT_FILE_NAME");



  this->Backup

    = this->Makefile->IsOn("CTEST_BACKUP_AND_RESTORE");

  this->EmptyBinDir

    = this->Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY");

  this->EmptyBinDirOnce

    = this->Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY_ONCE");



  minInterval

    = this->Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL");

  contDuration

    = this->Makefile->GetDefinition("CTEST_CONTINUOUS_DURATION");



  char updateVar[40];

  int i;

  for (i = 1; i < 10; ++i)

    {

    sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);

    const char *updateVal = this->Makefile->GetDefinition(updateVar);

    if ( updateVal )

      {

      if ( this->CVSCmd.empty() )

        {

        cmSystemTools::Error(updateVar,

          " specified without specifying CTEST_CVS_COMMAND.");

        return 12;

        }

      this->ExtraUpdates.push_back(updateVal);

      }

    }



  // in order to backup and restore we also must have the cvs root

  if (this->Backup && this->CVSCheckOut.empty())

    {

    cmSystemTools::Error(

      "Backup was requested without specifying CTEST_CVS_CHECKOUT.");

    return 3;

    }



  // make sure the required info is here

  if (this->SourceDir.empty() ||

      this->BinaryDir.empty() ||

      this->CTestCmd.empty())

    {

    std::string msg = "CTEST_SOURCE_DIRECTORY = ";

    msg += (!this->SourceDir.empty()) ? this->SourceDir.c_str() : "(Null)";

    msg += "\nCTEST_BINARY_DIRECTORY = ";

    msg += (!this->BinaryDir.empty()) ? this->BinaryDir.c_str() : "(Null)";

    msg += "\nCTEST_COMMAND = ";

    msg += (!this->CTestCmd.empty()) ? this->CTestCmd.c_str() : "(Null)";

    cmSystemTools::Error(

      "Some required settings in the configuration file were missing:\n",

      msg.c_str());

    return 4;

    }



  // if the dashboard root isn't specified then we can compute it from the

  // this->SourceDir

  if (this->CTestRoot.empty() )

    {

    this->CTestRoot = cmSystemTools::GetFilenamePath(this->SourceDir).c_str();

    }



  // the script may override the minimum continuous interval

  if (minInterval)

    {

    this->MinimumInterval = 60 * atof(minInterval);

    }

  if (contDuration)

    {

    this->ContinuousDuration = 60.0 * atof(contDuration);

    }





