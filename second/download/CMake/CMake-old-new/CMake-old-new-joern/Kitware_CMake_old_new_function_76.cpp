static void kwsysProcessSetExitException(kwsysProcess* cp, int sig)
{
  switch (sig) {
#ifdef SIGSEGV
    case SIGSEGV:
      KWSYSPE_CASE(Fault, "Segmentation fault");
      break;
#endif
#ifdef SIGBUS
#if !defined(SIGSEGV) || SIGBUS != SIGSEGV
    case SIGBUS:
      KWSYSPE_CASE(Fault, "Bus error");
      break;
#endif
#endif
#ifdef SIGFPE
    case SIGFPE:
      KWSYSPE_CASE(Numerical, "Floating-point exception");
      break;
#endif
#ifdef SIGILL
    case SIGILL:
      KWSYSPE_CASE(Illegal, "Illegal instruction");
      break;
#endif
#ifdef SIGINT
    case SIGINT:
      KWSYSPE_CASE(Interrupt, "User interrupt");
      break;
#endif
#ifdef SIGABRT
    case SIGABRT:
      KWSYSPE_CASE(Other, "Child aborted");
      break;
#endif
#ifdef SIGKILL
    case SIGKILL:
      KWSYSPE_CASE(Other, "Child killed");
      break;
#endif
#ifdef SIGTERM
    case SIGTERM:
      KWSYSPE_CASE(Other, "Child terminated");
      break;
#endif
#ifdef SIGHUP
    case SIGHUP:
      KWSYSPE_CASE(Other, "SIGHUP");
      break;
#endif
#ifdef SIGQUIT
    case SIGQUIT:
      KWSYSPE_CASE(Other, "SIGQUIT");
      break;
#endif
#ifdef SIGTRAP
    case SIGTRAP:
      KWSYSPE_CASE(Other, "SIGTRAP");
      break;
#endif
#ifdef SIGIOT
#if !defined(SIGABRT) || SIGIOT != SIGABRT
    case SIGIOT:
      KWSYSPE_CASE(Other, "SIGIOT");
      break;
#endif
#endif
#ifdef SIGUSR1
    case SIGUSR1:
      KWSYSPE_CASE(Other, "SIGUSR1");
      break;
#endif
#ifdef SIGUSR2
    case SIGUSR2:
      KWSYSPE_CASE(Other, "SIGUSR2");
      break;
#endif
#ifdef SIGPIPE
    case SIGPIPE:
      KWSYSPE_CASE(Other, "SIGPIPE");
      break;
#endif
#ifdef SIGALRM
    case SIGALRM:
      KWSYSPE_CASE(Other, "SIGALRM");
      break;
#endif
#ifdef SIGSTKFLT
    case SIGSTKFLT:
      KWSYSPE_CASE(Other, "SIGSTKFLT");
      break;
#endif
#ifdef SIGCHLD
    case SIGCHLD:
      KWSYSPE_CASE(Other, "SIGCHLD");
      break;
#elif defined(SIGCLD)
    case SIGCLD:
      KWSYSPE_CASE(Other, "SIGCLD");
      break;
#endif
#ifdef SIGCONT
    case SIGCONT:
      KWSYSPE_CASE(Other, "SIGCONT");
      break;
#endif
#ifdef SIGSTOP
    case SIGSTOP:
      KWSYSPE_CASE(Other, "SIGSTOP");
      break;
#endif
#ifdef SIGTSTP
    case SIGTSTP:
      KWSYSPE_CASE(Other, "SIGTSTP");
      break;
#endif
#ifdef SIGTTIN
    case SIGTTIN:
      KWSYSPE_CASE(Other, "SIGTTIN");
      break;
#endif
#ifdef SIGTTOU
    case SIGTTOU:
      KWSYSPE_CASE(Other, "SIGTTOU");
      break;
#endif
#ifdef SIGURG
    case SIGURG:
      KWSYSPE_CASE(Other, "SIGURG");
      break;
#endif
#ifdef SIGXCPU
    case SIGXCPU:
      KWSYSPE_CASE(Other, "SIGXCPU");
      break;
#endif
#ifdef SIGXFSZ
    case SIGXFSZ:
      KWSYSPE_CASE(Other, "SIGXFSZ");
      break;
#endif
#ifdef SIGVTALRM
    case SIGVTALRM:
      KWSYSPE_CASE(Other, "SIGVTALRM");
      break;
#endif
#ifdef SIGPROF
    case SIGPROF:
      KWSYSPE_CASE(Other, "SIGPROF");
      break;
#endif
#ifdef SIGWINCH
    case SIGWINCH:
      KWSYSPE_CASE(Other, "SIGWINCH");
      break;
#endif
#ifdef SIGPOLL
    case SIGPOLL:
      KWSYSPE_CASE(Other, "SIGPOLL");
      break;
#endif
#ifdef SIGIO
#if !defined(SIGPOLL) || SIGIO != SIGPOLL
    case SIGIO:
      KWSYSPE_CASE(Other, "SIGIO");
      break;
#endif
#endif
#ifdef SIGPWR
    case SIGPWR:
      KWSYSPE_CASE(Other, "SIGPWR");
      break;
#endif
#ifdef SIGSYS
    case SIGSYS:
      KWSYSPE_CASE(Other, "SIGSYS");
      break;
#endif
#ifdef SIGUNUSED
#if !defined(SIGSYS) || SIGUNUSED != SIGSYS
    case SIGUNUSED:
      KWSYSPE_CASE(Other, "SIGUNUSED");
      break;
#endif
#endif
    default:
      cp->ExitException = kwsysProcess_Exception_Other;
      sprintf(cp->ExitExceptionString, "Signal %d", sig);
      break;
  }
}