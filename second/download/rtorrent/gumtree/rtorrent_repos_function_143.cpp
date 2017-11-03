const char*
SignalHandler::as_string(unsigned int signum) {
  switch (signum) {
  case SIGHUP:
    return "Hangup detected";
  case SIGINT:
    return "Interrupt from keyboard";
  case SIGQUIT:
    return "Quit signal";
  case SIGILL:
    return "Illegal instruction";
  case SIGABRT:
    return "Abort signal";
  case SIGFPE:
    return "Floating point exception";
  case SIGKILL:
    return "Kill signal";
  case SIGSEGV:
    return "Segmentation fault";
  case SIGPIPE:
    return "Broken pipe";
  case SIGALRM:
    return "Timer signal";
  case SIGTERM:
    return "Termination signal";
  case SIGBUS:
    return "Bus error";
  default:
    return "Unlisted";
  }
}