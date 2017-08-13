std::string valueToString(double value) {
  // Allocate a buffer that is more than large enough to store the 16 digits of
  // precision requested below.
  char buffer[32];
  int len = -1;

// Print into the buffer. We need not request the alternative representation
// that always has a decimal point because JSON doesn't distingish the
// concepts of reals and integers.
#if defined(_MSC_VER) && defined(__STDC_SECURE_LIB__) // Use secure version with
                                                      // visual studio 2005 to
                                                      // avoid warning.
#if defined(WINCE)
  len = _snprintf(buffer, sizeof(buffer), "%.16g", value);
#else
  len = sprintf_s(buffer, sizeof(buffer), "%.16g", value);
#endif
#else
  if (isfinite(value)) {
    len = snprintf(buffer, sizeof(buffer), "%.16g", value);
  } else {
    // IEEE standard states that NaN values will not compare to themselves
    if (value != value) {
      len = snprintf(buffer, sizeof(buffer), "null");
    } else if (value < 0) {
      len = snprintf(buffer, sizeof(buffer), "-1e+9999");
    } else {
      len = snprintf(buffer, sizeof(buffer), "1e+9999");
    }
    // For those, we do not need to call fixNumLoc, but it is fast.
  }
#endif
  assert(len >= 0);
  fixNumericLocale(buffer, buffer + len);
  return buffer;
}