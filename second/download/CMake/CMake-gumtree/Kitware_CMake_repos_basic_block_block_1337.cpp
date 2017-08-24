{
    case kwsysProcess_Pipe_STDIN:
      pfile = &cp->PipeFileSTDIN;
      break;
    case kwsysProcess_Pipe_STDOUT:
      pfile = &cp->PipeFileSTDOUT;
      break;
    case kwsysProcess_Pipe_STDERR:
      pfile = &cp->PipeFileSTDERR;
      break;
    default:
      return 0;
  }