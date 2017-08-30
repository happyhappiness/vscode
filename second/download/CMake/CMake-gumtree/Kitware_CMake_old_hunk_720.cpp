      printf("Error in administrating child process: [%s]\n",

             kwsysProcess_GetErrorString(kp)); break;

    };

  

  if(result)

    {

    if(exception != kwsysProcess_GetExitException(kp))

