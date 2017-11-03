static void query_entry (char *s, size_t slen, MUTTMENU *m, int num)
{
  ENTRY *entry = &((ENTRY *) m->data)[num];

  entry->data->num = num;
  mutt_FormatString (s, slen, 0, MuttIndexWindow->cols, NONULL (QueryFormat), query_format_str,
		     (unsigned long) entry, MUTT_FORMAT_ARROWCURSOR);
}