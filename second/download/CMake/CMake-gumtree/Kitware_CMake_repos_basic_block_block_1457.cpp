{
          TerminateProcess(cp->ProcessInformation[i].hProcess, 255);
          WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
        }