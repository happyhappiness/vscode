(pipe) {
    case kwsysProcess_Pipe_STDIN:
      pPipeNative = cp->PipeNativeSTDIN;
      break;
    case kwsysProcess_Pipe_STDOUT:
      pPipeNative = cp->PipeNativeSTDOUT;
      break;
    case kwsysProcess_Pipe_STDERR:
      pPipeNative = cp->PipeNativeSTDERR;
      break;
    default:
      return;
  }