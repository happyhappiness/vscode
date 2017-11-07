void alias_entry (char *s, size_t slen, MUTTMENU *m, int num)
{
  mutt_FormatString (s, slen, NONULL (AliasFmt), alias_format_str, (unsigned long) ((ALIAS **) m->data)[num], M_FORMAT_ARROWCURSOR);
}