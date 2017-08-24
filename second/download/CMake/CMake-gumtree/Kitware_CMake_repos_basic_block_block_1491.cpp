{
  if (self->Snapshot) {
    if (self->P_Process32Next(self->Snapshot, &self->CurrentEntry)) {
      return 1;
    }
    CloseHandle(self->Snapshot);
    self->Snapshot = 0;
  }
  return 0;
}