{
      self->CurrentInfo = ((PSYSTEM_PROCESS_INFORMATION)(
        (char*)self->CurrentInfo + self->CurrentInfo->NextEntryDelta));
      return 1;
    }