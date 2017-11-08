void set_binmode(FILE *stream)
{
#ifdef O_BINARY
#  ifdef __HIGHC__
  _setmode(stream, O_BINARY);
#  else
  (void)setmode(fileno(stream), O_BINARY);
#  endif
#else
  (void)stream;
#endif
}