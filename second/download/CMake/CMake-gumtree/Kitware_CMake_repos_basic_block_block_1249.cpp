{
          /* All children have terminated.  Close the signal pipe
             write end so that no more notifications are sent to this
             object.  */
          kwsysProcessCleanupDescriptor(&cp->SignalPipe);

          /* TODO: Once the children have terminated, switch
             WaitForData to use a non-blocking read to get the
             rest of the data from the pipe.  This is needed when
             grandchildren keep the output pipes open.  */
        }