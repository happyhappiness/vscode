{
  /* Get a handle to the NT runtime module that should already be
     loaded in this program.  This does not actually increment the
     reference count to the module so we do not need to close the
     handle.  */
  HMODULE hNT = GetModuleHandleW(L"ntdll.dll");
  if (hNT) {
    /* Get pointers to the needed API functions.  */
    self->P_ZwQuerySystemInformation =
      ((ZwQuerySystemInformationType)GetProcAddress(
        hNT, "ZwQuerySystemInformation"));
  }
  if (!self->P_ZwQuerySystemInformation) {
    return 0;
  }

  /* Allocate an initial process information buffer.  */
  self->BufferSize = 32768;
  self->Buffer = (char*)malloc(self->BufferSize);
  return self->Buffer ? 1 : 0;
}