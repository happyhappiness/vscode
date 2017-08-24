(honor_umask) {
    mode_t currentMask = umask(0);
    umask(currentMask);
    mode &= ~currentMask;
  }