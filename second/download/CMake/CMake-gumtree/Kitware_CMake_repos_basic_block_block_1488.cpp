(!self->P_Process32First(self->Snapshot, &self->CurrentEntry)) {
    CloseHandle(self->Snapshot);
    self->Snapshot = 0;
    return 0;
  }