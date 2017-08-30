      }

    }



  /* Create the child in a suspended state so we can wait until all

     children have been created before running any one.  */

  if(!CreateProcess(0, cp->Commands[index], 0, 0, TRUE, CREATE_SUSPENDED, 0,

                    0, &si->StartupInfo, &cp->ProcessInformation[index]))

    {

    return 0;

    }



  /* Successfully created this child process.  Close the current

     process's copies of the inherited stdout and stdin handles.  The

