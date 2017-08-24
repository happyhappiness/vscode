{
#ifdef _WIN32
  HANDLE hFile1, hFile2;

  hFile1 =
    CreateFileW(Encoding::ToWide(file1).c_str(), GENERIC_READ, FILE_SHARE_READ,
                NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
  hFile2 =
    CreateFileW(Encoding::ToWide(file2).c_str(), GENERIC_READ, FILE_SHARE_READ,
                NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
  if (hFile1 == INVALID_HANDLE_VALUE || hFile2 == INVALID_HANDLE_VALUE) {
    if (hFile1 != INVALID_HANDLE_VALUE) {
      CloseHandle(hFile1);
    }
    if (hFile2 != INVALID_HANDLE_VALUE) {
      CloseHandle(hFile2);
    }
    return false;
  }

  BY_HANDLE_FILE_INFORMATION fiBuf1;
  BY_HANDLE_FILE_INFORMATION fiBuf2;
  GetFileInformationByHandle(hFile1, &fiBuf1);
  GetFileInformationByHandle(hFile2, &fiBuf2);
  CloseHandle(hFile1);
  CloseHandle(hFile2);
  return (fiBuf1.dwVolumeSerialNumber == fiBuf2.dwVolumeSerialNumber &&
          fiBuf1.nFileIndexHigh == fiBuf2.nFileIndexHigh &&
          fiBuf1.nFileIndexLow == fiBuf2.nFileIndexLow);
#else
  struct stat fileStat1, fileStat2;
  if (stat(file1.c_str(), &fileStat1) == 0 &&
      stat(file2.c_str(), &fileStat2) == 0) {
    // see if the files are the same file
    // check the device inode and size
    if (memcmp(&fileStat2.st_dev, &fileStat1.st_dev,
               sizeof(fileStat1.st_dev)) == 0 &&
        memcmp(&fileStat2.st_ino, &fileStat1.st_ino,
               sizeof(fileStat1.st_ino)) == 0 &&
        fileStat2.st_size == fileStat1.st_size) {
      return true;
    }
  }
  return false;
#endif
}