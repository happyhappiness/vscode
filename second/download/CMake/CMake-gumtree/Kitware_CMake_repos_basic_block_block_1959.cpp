(DLLProc != NULL)
            (DLLProc)(GetCurrentProcess(), &bIsWindows64Bit);
          else
            bIsWindows64Bit = false