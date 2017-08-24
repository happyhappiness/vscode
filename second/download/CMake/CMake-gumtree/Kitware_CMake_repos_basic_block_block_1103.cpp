{
  char** pfile;
  if (!cp) {
    return 0;
  }
  switch (prPipe) {
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
  if (*pfile) {
    free(*pfile);
    *pfile = 0;
  }
  if (file) {
    *pfile = (char*)malloc(strlen(file) + 1);
    if (!*pfile) {
      return 0;
    }
    strcpy(*pfile, file);
  }

  /* If we are redirecting the pipe, do not share it or use a native
     pipe.  */
  if (*pfile) {
    kwsysProcess_SetPipeNative(cp, prPipe, 0);
    kwsysProcess_SetPipeShared(cp, prPipe, 0);
  }
  return 1;
}