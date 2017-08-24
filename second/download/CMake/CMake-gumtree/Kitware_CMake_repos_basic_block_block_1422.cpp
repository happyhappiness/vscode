{
    DWORD dummy;
    KWSYSPE_DEBUG((stderr, "waker %d writing byte\n", td->Index));
    WriteFile(td->Write, "", 1, &dummy, 0);
    KWSYSPE_DEBUG((stderr, "waker %d wrote byte\n", td->Index));
  }