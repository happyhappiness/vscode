(cp->TimeoutExpired) {
    /* The timeout expired.  */
    cp->State = kwsysProcess_State_Expired;
  }