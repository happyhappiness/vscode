{
        // Windows XP and .NET server.
        typedef BOOL(CALLBACK * LPFNPROC)(HANDLE, BOOL*);
        HINSTANCE hKernelDLL;
        LPFNPROC DLLProc;

        // Load the Kernel32 DLL.
        hKernelDLL = LoadLibraryW(L"kernel32");
        if (hKernelDLL != NULL) {
          // Only XP and .NET Server support IsWOW64Process so... Load
          // dynamically!
          DLLProc = (LPFNPROC)GetProcAddress(hKernelDLL, "IsWow64Process");

          // If the function address is valid, call the function.
          if (DLLProc != NULL)
            (DLLProc)(GetCurrentProcess(), &bIsWindows64Bit);
          else
            bIsWindows64Bit = false;

          // Free the DLL module.
          FreeLibrary(hKernelDLL);
        }
      }