

void cmCTestScriptHandler::UpdateElapsedTime()

{

  if (m_LocalGenerator)

    {

    // set the current elapsed time

    char timeString[20];

    int itime = static_cast<unsigned int>(cmSystemTools::GetTime()

                                          - m_ScriptStartTime);

    sprintf(timeString,"%i",itime);

    m_LocalGenerator->GetMakefile()->AddDefinition("CTEST_ELAPSED_TIME",

                                                   timeString);

    }

}

