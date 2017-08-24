{
  if (!cp) {
    return "Process management structure could not be allocated";
  } else if (cp->State == kwsysProcess_State_Error) {
    return cp->ErrorMessage;
  }
  return "Success";
}