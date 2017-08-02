{
      report_good(false, entry.str);
      printf("expected 0x%04X, got 0x%04X\n", entry.chr, uc);
      return false;
    }