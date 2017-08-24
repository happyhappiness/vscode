{
    BY_HANDLE_FILE_INFORMATION fi1;
    BY_HANDLE_FILE_INFORMATION fi2;
    GetFileInformationByHandle(h1, &fi1);
    GetFileInformationByHandle(h2, &fi2);
    result = (fi1.dwVolumeSerialNumber == fi2.dwVolumeSerialNumber &&
              fi1.nFileIndexHigh == fi2.nFileIndexHigh &&
              fi1.nFileIndexLow == fi2.nFileIndexLow);
  }