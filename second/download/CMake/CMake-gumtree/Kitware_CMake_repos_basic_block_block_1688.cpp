((ll = readlink("/proc/self/exe", buf, 1024)) > 0) {
      buf[ll] = '\0';
      binary = buf;
    } else {
      binary = "/proc/self/exe";
    }