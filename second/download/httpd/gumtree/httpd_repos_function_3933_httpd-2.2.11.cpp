int
pcre_get_stringnumber(const pcre *code, const char *stringname)
{
int rc;
int entrysize;
int top, bot;
uschar *nametable;

if ((rc = pcre_fullinfo(code, NULL, PCRE_INFO_NAMECOUNT, &top)) != 0)
  return rc;
if (top <= 0) return PCRE_ERROR_NOSUBSTRING;

if ((rc = pcre_fullinfo(code, NULL, PCRE_INFO_NAMEENTRYSIZE, &entrysize)) != 0)
  return rc;
if ((rc = pcre_fullinfo(code, NULL, PCRE_INFO_NAMETABLE, &nametable)) != 0)
  return rc;

bot = 0;
while (top > bot)
  {
  int mid = (top + bot) / 2;
  uschar *entry = nametable + entrysize*mid;
  int c = strcmp(stringname, (char *)(entry + 2));
  if (c == 0) return (entry[0] << 8) + entry[1];
  if (c > 0) bot = mid + 1; else top = mid;
  }

return PCRE_ERROR_NOSUBSTRING;
}