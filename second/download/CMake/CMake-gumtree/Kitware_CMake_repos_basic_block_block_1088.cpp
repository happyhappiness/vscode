{
  /* Allocate a process control structure.  */
  kwsysProcess* cp = (kwsysProcess*)malloc(sizeof(kwsysProcess));
  if (!cp) {
    return 0;
  }
  memset(cp, 0, sizeof(kwsysProcess));

  /* Share stdin with the parent process by default.  */
  cp->PipeSharedSTDIN = 1;

  /* No native pipes by default.  */
  cp->PipeNativeSTDIN[0] = -1;
  cp->PipeNativeSTDIN[1] = -1;
  cp->PipeNativeSTDOUT[0] = -1;
  cp->PipeNativeSTDOUT[1] = -1;
  cp->PipeNativeSTDERR[0] = -1;
  cp->PipeNativeSTDERR[1] = -1;

  /* Set initial status.  */
  cp->State = kwsysProcess_State_Starting;

  return cp;
}