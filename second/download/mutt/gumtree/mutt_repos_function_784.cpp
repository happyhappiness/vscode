static void snd_entry (char *b, size_t blen, MUTTMENU *menu, int num)
{
  mutt_FormatString (b, blen, 0, MuttIndexWindow->cols, NONULL (AttachFormat), mutt_attach_fmt,
	    (unsigned long)(((ATTACHPTR **) menu->data)[num]),
	    MUTT_FORMAT_STAT_FILE | MUTT_FORMAT_ARROWCURSOR);
}