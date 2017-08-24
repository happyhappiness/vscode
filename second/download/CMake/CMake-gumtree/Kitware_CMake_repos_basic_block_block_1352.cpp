{
  KWSYSPE_IDX_CHK("GetExceptionString called with NULL process management "
                  "structure or index out of bound")
  if (cp->ProcessResults[idx].State == kwsysProcess_StateByIndex_Exception) {
    return cp->ProcessResults[idx].ExitExceptionString;
  }
  return "No exception";
}