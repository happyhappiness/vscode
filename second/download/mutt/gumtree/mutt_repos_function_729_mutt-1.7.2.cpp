static void crypt_entry (char *s, size_t l, MUTTMENU * menu, int num)
{
  crypt_key_t **key_table = (crypt_key_t **) menu->data;
  crypt_entry_t entry;
  
  entry.key = key_table[num];
  entry.num = num + 1;

  mutt_FormatString (s, l, 0, MuttIndexWindow->cols, NONULL (PgpEntryFormat), crypt_entry_fmt, 
		     (unsigned long) &entry, MUTT_FORMAT_ARROWCURSOR);
}