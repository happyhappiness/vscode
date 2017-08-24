(index = 0; index < cp->NumberOfCommands; ++index) {
    if (cp->ProcessInformation[index].hProcess == cp->ProcessEvents[event]) {
      break;
    }
  }