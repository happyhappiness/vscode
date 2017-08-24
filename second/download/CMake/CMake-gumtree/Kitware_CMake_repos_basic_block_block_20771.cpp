{
        /* Windows will terminate the process after the control handler */
        /* returns. After that it will just terminate our process. Therefore */
        /* block the signal handler so the main loop has some time to pick */
        /* up the signal and do something for a few seconds. */
        Sleep(INFINITE);
        return TRUE;
      }