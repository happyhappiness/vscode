#endif

#endif

    default:

      cp->ExitException = kwsysProcess_Exception_Other;

      sprintf(cp->ExitExceptionString, "Signal %d", sig);

      break;

  }

}

#undef KWSYSPE_CASE



/*--------------------------------------------------------------------------*/

/* When the child process encounters an error before its program is

   invoked, this is called to report the error to the parent and

   exit.  */

