static void mix_entry (char *b, size_t blen, MUTTMENU *menu, int num)
{
  REMAILER **type2_list = (REMAILER **) menu->data;
  mutt_FormatString (b, blen, 0, MuttIndexWindow->cols, NONULL (MixEntryFormat), mix_entry_fmt,
		     (unsigned long) type2_list[num], MUTT_FORMAT_ARROWCURSOR);
}