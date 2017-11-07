static void snd_entry (char *b, size_t blen, MUTTMENU *menu, int num)
{
    mutt_FormatString (b, blen, NONULL (AttachFormat), mutt_attach_fmt,
	    (unsigned long)(((ATTACHPTR **) menu->data)[num]),
	    M_FORMAT_STAT_FILE | M_FORMAT_ARROWCURSOR);
}