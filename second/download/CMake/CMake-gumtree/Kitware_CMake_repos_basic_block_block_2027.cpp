(ExpandEnvironmentStringsW(data, expanded, dwExpandedSize)) {
          value = Encoding::ToNarrow(expanded);
          valueset = true;
        }