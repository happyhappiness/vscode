{
    // set the current elapsed time
    char timeString[20];
    int itime = static_cast<unsigned int>(cmSystemTools::GetTime()
                                          - this->ScriptStartTime);
    sprintf(timeString,"%i",itime);
    this->LocalGenerator->GetMakefile()->AddDefinition("CTEST_ELAPSED_TIME",
                                                   timeString);
    }