f(trust == NULL) {
    failf(data, "SSL: error getting certificate chain");
    CFRelease(array);
    return CURLE_OUT_OF_MEMORY;
  }
  else if(ret != noErr) {
    CFRelease(array);
    return sslerr_to_curlerr(data, ret);
  }