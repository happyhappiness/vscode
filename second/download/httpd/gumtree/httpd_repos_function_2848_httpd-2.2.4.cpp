static
int getEncodingIndex(const char *name)
{
  static const char *encodingNames[] = {
    KW_ISO_8859_1,
    KW_US_ASCII,
    KW_UTF_8,
    KW_UTF_16,
    KW_UTF_16BE,
    KW_UTF_16LE,
  };
  int i;
  if (name == 0)
    return NO_ENC;
  for (i = 0; i < (int)(sizeof(encodingNames)/sizeof(encodingNames[0])); i++)
    if (streqci(name, encodingNames[i]))
      return i;
  return UNKNOWN_ENC;
}