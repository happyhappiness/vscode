(src.str != NULL) {
        str = ::SysAllocStringByteLen((char*)str, ::SysStringByteLen(str));
      } else {
        str = ::SysAllocStringByteLen(NULL, 0);
      }