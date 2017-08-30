    case STATUS_NO_MEMORY:

    default:

      cp->ExitException = kwsysProcess_Exception_Other;

      sprintf(cp->ExitExceptionString, "Exit code 0x%x\n", code);

      break;

    }

}

