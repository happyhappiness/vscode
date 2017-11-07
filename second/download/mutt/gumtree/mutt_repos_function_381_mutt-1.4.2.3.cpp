static void query_entry (char *s, size_t slen, MUTTMENU *m, int num)
{
  ENTRY *table = (ENTRY *) m->data;
  char buf[SHORT_STRING] = "";

  /* need a query format ... hard coded constants are not good */
  while (FirstColumn + SecondColumn > 70)
  {
    FirstColumn = FirstColumn * 3 / 4;
    SecondColumn = SecondColumn * 3 / 4;
    if (FirstColumn < QUERY_MIN_COLUMN_LENGHT)
      FirstColumn = QUERY_MIN_COLUMN_LENGHT;
    if (SecondColumn < QUERY_MIN_COLUMN_LENGHT)
      SecondColumn = QUERY_MIN_COLUMN_LENGHT;
  }

  rfc822_write_address (buf, sizeof (buf), table[num].data->addr);

  snprintf (s, slen, " %c %3d %-*.*s %-*.*s %s", 
	    table[num].tagged ? '*':' ',
	    num+1,
	    FirstColumn+2,
	    FirstColumn+2,
	    NONULL (table[num].data->name),
	    SecondColumn+2,
	    SecondColumn+2,
	    buf,
	    NONULL (table[num].data->other));
}