f(ret != noErr) {
    CFRelease(array);
    return sslerr_to_curlerr(data, ret);
  }