
    case STATUS_NO_MEMORY:
    default:
      cp->ProcessResults[idx].ExitException = kwsysProcess_Exception_Other;
      _snprintf(cp->ProcessResults[idx].ExitExceptionString,
                KWSYSPE_PIPE_BUFFER_SIZE, "Exit code 0x%x\n", code);
      break;
  }
}
