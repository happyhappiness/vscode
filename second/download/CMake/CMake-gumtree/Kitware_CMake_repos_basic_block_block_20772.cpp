{
    case CTRL_C_EVENT:
      return uv__signal_dispatch(SIGINT);

    case CTRL_BREAK_EVENT:
      return uv__signal_dispatch(SIGBREAK);

    case CTRL_CLOSE_EVENT:
      if (uv__signal_dispatch(SIGHUP)) {
        /* Windows will terminate the process after the control handler */
        /* returns. After that it will just terminate our process. Therefore */
        /* block the signal handler so the main loop has some time to pick */
        /* up the signal and do something for a few seconds. */
        Sleep(INFINITE);
        return TRUE;
      }
      return FALSE;

    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
      /* These signals are only sent to services. Services have their own */
      /* notification mechanism, so there's no point in handling these. */

    default:
      /* We don't handle these. */
      return FALSE;
  }