{
    self->P_CreateToolhelp32Snapshot =
      ((CreateToolhelp32SnapshotType)GetProcAddress(
        hKernel, "CreateToolhelp32Snapshot"));
    self->P_Process32First =
      ((Process32FirstType)GetProcAddress(hKernel, "Process32First"));
    self->P_Process32Next =
      ((Process32NextType)GetProcAddress(hKernel, "Process32Next"));
  }