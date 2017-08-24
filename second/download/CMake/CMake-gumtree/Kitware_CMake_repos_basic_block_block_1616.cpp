{
        size_t len;
        const char* opnd;

        opnd = OPERAND(scan);
        // Inline the first character, for speed.
        if (*opnd != *reginput)
          return (0);
        len = strlen(opnd);
        if (len > 1 && strncmp(opnd, reginput, len) != 0)
          return (0);
        reginput += len;
      }