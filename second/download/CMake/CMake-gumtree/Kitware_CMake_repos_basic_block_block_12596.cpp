r(j = 0; j < numsymbols; j++)
    {
      if (lengths[j] != i) continue;
      if (add_value(a, code, j, codebits, i) != ARCHIVE_OK)
        return (ARCHIVE_FATAL);
      codebits++;
      if (--symbolsleft <= 0) { break; break; }
    }