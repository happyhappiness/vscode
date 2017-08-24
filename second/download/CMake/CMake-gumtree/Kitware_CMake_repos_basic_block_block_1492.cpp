{
    TerminateProcess(h, 255);
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
  }