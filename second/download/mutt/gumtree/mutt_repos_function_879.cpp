static char *get_sort_str (char *buf, size_t buflen, int method)
{
  snprintf (buf, buflen, "%s%s%s",
	    (method & SORT_REVERSE) ? "reverse-" : "",
	    (method & SORT_LAST) ? "last-" : "",
	    mutt_getnamebyvalue (method & SORT_MASK, SortMethods));
  return buf;
}