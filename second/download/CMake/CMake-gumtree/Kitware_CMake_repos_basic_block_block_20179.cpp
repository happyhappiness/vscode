{
    /* Remove read-only attribute */
    FILE_BASIC_INFORMATION basic = { 0 };

    basic.FileAttributes = info.dwFileAttributes & ~(FILE_ATTRIBUTE_READONLY);

    status = pNtSetInformationFile(handle,
                                   &iosb,
                                   &basic,
                                   sizeof basic,
                                   FileBasicInformation);
    if (!NT_SUCCESS(status)) {
      SET_REQ_WIN32_ERROR(req, pRtlNtStatusToDosError(status));
      CloseHandle(handle);
      return;
    }
  }