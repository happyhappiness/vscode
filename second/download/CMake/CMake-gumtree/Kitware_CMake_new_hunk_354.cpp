
// Read an integer value from an input stream.
template <class T>
std::istream& IOStreamScanTemplate(std::istream& is, T& value, char type)
{
  int state = std::ios_base::goodbit;

  // Skip leading whitespace.
  std::istream::sentry okay(is);

  if (okay) {
    try {
      // Copy the string to a buffer and construct the format string.
      char buffer[KWSYS_IOS_INT64_MAX_DIG];
#if defined(_MSC_VER)
      char format[] = "%I64_";
      const int typeIndex = 4;
#else
      char format[] = "%ll_";
      const int typeIndex = 3;
#endif
      switch (IOStreamScanStream(is, buffer)) {
        case 8:
          format[typeIndex] = 'o';
          break;
        case 0: // Default to decimal if not told otherwise.
        case 10:
          format[typeIndex] = type;
          break;
        case 16:
          format[typeIndex] = 'x';
          break;
      };

      // Use sscanf to parse the number from the buffer.
      T result;
      int success = (sscanf(buffer, format, &result) == 1) ? 1 : 0;

      // Set flags for resulting state.
      if (is.peek() == EOF) {
        state |= std::ios_base::eofbit;
      }
      if (!success) {
        state |= std::ios_base::failbit;
      } else {
        value = result;
      }
    } catch (...) {
      state |= std::ios_base::badbit;
    }
  }

  is.setstate(std::ios_base::iostate(state));
  return is;
}

// Print an integer value to an output stream.
template <class T>
std::ostream& IOStreamPrintTemplate(std::ostream& os, T value, char type)
{
  std::ostream::sentry okay(os);
  if (okay) {
    try {
      // Construct the format string.
      char format[8];
      char* f = format;
      *f++ = '%';
      if (os.flags() & std::ios_base::showpos) {
        *f++ = '+';
      }
      if (os.flags() & std::ios_base::showbase) {
        *f++ = '#';
      }
#if defined(_MSC_VER)
      *f++ = 'I';
      *f++ = '6';
      *f++ = '4';
#else
      *f++ = 'l';
      *f++ = 'l';
#endif
      long bflags = os.flags() & std::ios_base::basefield;
      if (bflags == std::ios_base::oct) {
        *f++ = 'o';
      } else if (bflags != std::ios_base::hex) {
        *f++ = type;
      } else if (os.flags() & std::ios_base::uppercase) {
        *f++ = 'X';
      } else {
        *f++ = 'x';
      }
      *f = '\0';

      // Use sprintf to print to a buffer and then write the
      // buffer to the stream.
      char buffer[2 * KWSYS_IOS_INT64_MAX_DIG];
      sprintf(buffer, format, value);
      os << buffer;
    } catch (...) {
      os.clear(os.rdstate() | std::ios_base::badbit);
    }
  }
  return os;
}

#if !KWSYS_IOS_HAS_ISTREAM_LONG_LONG
// Implement input stream operator for IOStreamSLL.
std::istream& IOStreamScan(std::istream& is, IOStreamSLL& value)
{
