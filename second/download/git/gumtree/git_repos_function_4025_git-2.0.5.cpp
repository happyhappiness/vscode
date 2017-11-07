static int sane_ident_split(struct ident_split *person)
{
	if (!person->name_begin || !person->name_end ||
	    person->name_begin == person->name_end)
		return 0; /* no human readable name */
	if (!person->mail_begin || !person->mail_end ||
	    person->mail_begin == person->mail_end)
		return 0; /* no usable mail */
	if (!person->date_begin || !person->date_end ||
	    !person->tz_begin || !person->tz_end)
		return 0;
	return 1;
}