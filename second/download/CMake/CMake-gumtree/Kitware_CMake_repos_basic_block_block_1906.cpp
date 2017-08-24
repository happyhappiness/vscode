{
      delete[] buf;
      allocSize *= 2;
      buf = new char[allocSize];
      if (!buf) {
        break;
      }
      buf[0] = ' ';
      len = allocSize - 2; // keep space for leading and trailing space
      err = sysctlbyname("machdep.cpu.features", buf + 1, &len, NULL, 0);
    }