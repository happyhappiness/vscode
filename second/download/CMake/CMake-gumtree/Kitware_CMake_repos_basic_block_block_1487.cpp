{
    CloseHandle(self->Snapshot);
    self->Snapshot = 0;
    return 0;
  }