<class T>
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