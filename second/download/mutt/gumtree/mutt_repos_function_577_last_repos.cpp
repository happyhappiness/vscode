static void alias_entry (char *s, size_t slen, MUTTMENU *m, int num)
{
  mutt_FormatString (s, slen, 0, MuttIndexWindow->cols, NONULL (AliasFmt), alias_format_str, (unsigned long) ((ALIAS **) m->data)[num], MUTT_FORMAT_ARROWCURSOR);
}