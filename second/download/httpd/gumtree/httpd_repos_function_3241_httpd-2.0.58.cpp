const char *
pcre_version(void)
{
return XSTRING(PCRE_MAJOR) "." XSTRING(PCRE_MINOR) " " XSTRING(PCRE_DATE);
}