(dwType == REG_SZ) {
        value = Encoding::ToNarrow(data);
        valueset = true;
      } else if (dwType == REG_EXPAND_SZ) {
        wchar_t expanded[1024];
        DWORD dwExpandedSize = sizeof(expanded) / sizeof(expanded[0]);
        if (ExpandEnvironmentStringsW(data, expanded, dwExpandedSize)) {
          value = Encoding::ToNarrow(expanded);
          valueset = true;
        }
      }