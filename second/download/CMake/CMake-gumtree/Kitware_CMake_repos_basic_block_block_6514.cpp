f(ret != noErr) {
    CFRelease(trust);
    return sslerr_to_curlerr(data, ret);
  }