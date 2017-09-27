         case CTRL_LOGOFF_EVENT:
         case CTRL_SHUTDOWN_EVENT:
             /* for Terminate signals, shut down the server.
              * Wait for Apache to terminate, but respond
              * after a reasonable time to tell the system
              * that we did attempt to shut ourself down.
-             * THESE EVENTS WILL NOT OCCUR UNDER WIN9x!
              */
             fprintf(stderr, "Apache server shutdown initiated...\n");
             ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
             Sleep(30000);
             return TRUE;
     }
