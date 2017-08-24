(i = 0; i < cp->NumberOfCommands; ++i) {
        if (cp->ProcessInformation[i].hProcess) {
          TerminateProcess(cp->ProcessInformation[i].hProcess, 255);
          WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
        }
      }