{
  if (!cp) {
    return;
  }
  /* Reset start time. */
  cp->StartTime = kwsysProcessTimeGetCurrent();
}