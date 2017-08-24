(pipe) {
    case kwsysProcess_Pipe_STDIN:
      cp->PipeSharedSTDIN = shared ? 1 : 0;
      break;
    case kwsysProcess_Pipe_STDOUT:
      cp->PipeSharedSTDOUT = shared ? 1 : 0;
      break;
    case kwsysProcess_Pipe_STDERR:
      cp->PipeSharedSTDERR = shared ? 1 : 0;
      break;
    default:
      return;
  }