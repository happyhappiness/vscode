static int PTRCALL
NS(initScanContent)(const ENCODING *enc, const char *ptr, const char *end,
                    const char **nextTokPtr)
{
  return initScan(NS(encodings), (const INIT_ENCODING *)enc,
                  XML_CONTENT_STATE, ptr, end, nextTokPtr);
}