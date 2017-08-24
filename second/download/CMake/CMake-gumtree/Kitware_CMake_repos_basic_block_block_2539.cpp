((p = kwsysProcess_WaitForData(kp, &data, &length, pUserTimeout))) {
      if (output) {
        if (poll && p == kwsysProcess_Pipe_Timeout) {
          fprintf(stdout, "WaitForData timeout reached.\n");
          fflush(stdout);

          /* Count the number of times we polled without getting data.
             If it is excessive then kill the child and fail.  */
          if (++poll >= MAXPOLL) {
            fprintf(stdout, "Poll count reached limit %d.\n", MAXPOLL);
            kwsysProcess_Kill(kp);
          }
        } else {
          fwrite(data, 1, (size_t)length, stdout);
          fflush(stdout);
        }
      }
      if (poll) {
        /* Delay to avoid busy loop during polling.  */
        testProcess_usleep(100000);
      }
      if (delay) {
/* Purposely sleeping only on Win32 to let pipe fill up.  */
#if defined(_WIN32)
        testProcess_usleep(100000);
#endif
      }
    }