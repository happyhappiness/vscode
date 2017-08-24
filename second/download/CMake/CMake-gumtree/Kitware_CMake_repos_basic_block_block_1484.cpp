(self->CurrentInfo->NextEntryDelta > 0) {
      self->CurrentInfo = ((PSYSTEM_PROCESS_INFORMATION)(
        (char*)self->CurrentInfo + self->CurrentInfo->NextEntryDelta));
      return 1;
    }