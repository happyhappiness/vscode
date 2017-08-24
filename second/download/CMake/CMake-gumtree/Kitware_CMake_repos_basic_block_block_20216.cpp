{
  FILE_ALL_INFORMATION file_info;
  FILE_FS_VOLUME_INFORMATION volume_info;
  NTSTATUS nt_status;
  IO_STATUS_BLOCK io_status;

  nt_status = pNtQueryInformationFile(handle,
                                      &io_status,
                                      &file_info,
                                      sizeof file_info,
                                      FileAllInformation);

  /* Buffer overflow (a warning status code) is expected here. */
  if (NT_ERROR(nt_status)) {
    SetLastError(pRtlNtStatusToDosError(nt_status));
    return -1;
  }

  nt_status = pNtQueryVolumeInformationFile(handle,
                                            &io_status,
                                            &volume_info,
                                            sizeof volume_info,
                                            FileFsVolumeInformation);

  /* Buffer overflow (a warning status code) is expected here. */
  if (io_status.Status == STATUS_NOT_IMPLEMENTED) {
    statbuf->st_dev = 0;
  } else if (NT_ERROR(nt_status)) {
    SetLastError(pRtlNtStatusToDosError(nt_status));
    return -1;
  } else {
    statbuf->st_dev = volume_info.VolumeSerialNumber;
  }

  /* Todo: st_mode should probably always be 0666 for everyone. We might also
   * want to report 0777 if the file is a .exe or a directory.
   *
   * Currently it's based on whether the 'readonly' attribute is set, which
   * makes little sense because the semantics are so different: the 'read-only'
   * flag is just a way for a user to protect against accidental deletion, and
   * serves no security purpose. Windows uses ACLs for that.
   *
   * Also people now use uv_fs_chmod() to take away the writable bit for good
   * reasons. Windows however just makes the file read-only, which makes it
   * impossible to delete the file afterwards, since read-only files can't be
   * deleted.
   *
   * IOW it's all just a clusterfuck and we should think of something that
   * makes slightly more sense.
   *
   * And uv_fs_chmod should probably just fail on windows or be a total no-op.
   * There's nothing sensible it can do anyway.
   */
  statbuf->st_mode = 0;

  if (file_info.BasicInformation.FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
    /*
     * It is possible for a file to have FILE_ATTRIBUTE_REPARSE_POINT but not have
     * any link data. In that case DeviceIoControl() in fs__readlink_handle() sets
     * the last error to ERROR_NOT_A_REPARSE_POINT. Then the stat result mode
     * calculated below will indicate a normal directory or file, as if
     * FILE_ATTRIBUTE_REPARSE_POINT was not present.
     */
    if (fs__readlink_handle(handle, NULL, &statbuf->st_size) == 0) {
      statbuf->st_mode |= S_IFLNK;
    } else if (GetLastError() != ERROR_NOT_A_REPARSE_POINT) {
      return -1;
    }
  }

  if (statbuf->st_mode == 0) {
    if (file_info.BasicInformation.FileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      statbuf->st_mode |= _S_IFDIR;
      statbuf->st_size = 0;
    } else {
      statbuf->st_mode |= _S_IFREG;
      statbuf->st_size = file_info.StandardInformation.EndOfFile.QuadPart;
    }
  }

  if (file_info.BasicInformation.FileAttributes & FILE_ATTRIBUTE_READONLY)
    statbuf->st_mode |= _S_IREAD | (_S_IREAD >> 3) | (_S_IREAD >> 6);
  else
    statbuf->st_mode |= (_S_IREAD | _S_IWRITE) | ((_S_IREAD | _S_IWRITE) >> 3) |
                        ((_S_IREAD | _S_IWRITE) >> 6);

  FILETIME_TO_TIMESPEC(statbuf->st_atim, file_info.BasicInformation.LastAccessTime);
  FILETIME_TO_TIMESPEC(statbuf->st_ctim, file_info.BasicInformation.ChangeTime);
  FILETIME_TO_TIMESPEC(statbuf->st_mtim, file_info.BasicInformation.LastWriteTime);
  FILETIME_TO_TIMESPEC(statbuf->st_birthtim, file_info.BasicInformation.CreationTime);

  statbuf->st_ino = file_info.InternalInformation.IndexNumber.QuadPart;

  /* st_blocks contains the on-disk allocation size in 512-byte units. */
  statbuf->st_blocks =
      file_info.StandardInformation.AllocationSize.QuadPart >> 9ULL;

  statbuf->st_nlink = file_info.StandardInformation.NumberOfLinks;

  /* The st_blksize is supposed to be the 'optimal' number of bytes for reading
   * and writing to the disk. That is, for any definition of 'optimal' - it's
   * supposed to at least avoid read-update-write behavior when writing to the
   * disk.
   *
   * However nobody knows this and even fewer people actually use this value,
   * and in order to fill it out we'd have to make another syscall to query the
   * volume for FILE_FS_SECTOR_SIZE_INFORMATION.
   *
   * Therefore we'll just report a sensible value that's quite commonly okay
   * on modern hardware.
   */
  statbuf->st_blksize = 2048;

  /* Todo: set st_flags to something meaningful. Also provide a wrapper for
   * chattr(2).
   */
  statbuf->st_flags = 0;

  /* Windows has nothing sensible to say about these values, so they'll just
   * remain empty.
   */
  statbuf->st_gid = 0;
  statbuf->st_uid = 0;
  statbuf->st_rdev = 0;
  statbuf->st_gen = 0;

  return 0;
}