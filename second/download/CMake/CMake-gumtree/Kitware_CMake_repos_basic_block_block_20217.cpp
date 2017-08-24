(io_status.Status == STATUS_NOT_IMPLEMENTED) {
    statbuf->st_dev = 0;
  } else if (NT_ERROR(nt_status)) {
    SetLastError(pRtlNtStatusToDosError(nt_status));
    return -1;
  } else {
    statbuf->st_dev = volume_info.VolumeSerialNumber;
  }