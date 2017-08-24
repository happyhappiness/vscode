{
    /* Get pointers to the needed API functions.  */
    self->P_ZwQuerySystemInformation =
      ((ZwQuerySystemInformationType)GetProcAddress(
        hNT, "ZwQuerySystemInformation"));
  }