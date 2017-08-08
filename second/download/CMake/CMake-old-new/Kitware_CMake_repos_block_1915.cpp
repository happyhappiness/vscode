{
            fprintf(stdout, "Poll count reached limit %d.\n", MAXPOLL);
            kwsysProcess_Kill(kp);
          }