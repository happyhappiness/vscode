	value_list_t vl = VALUE_LIST_INIT;

	if (fields_num < 3)
	{
		DEBUG ("cmd putval: Wrong number of fields: %i",
			       	fields_num);
		fprintf (fh, "-1 Wrong number of fields: Got %i, "
				"expected at least 3.\n",
				fields_num);
		fflush (fh);
		return (-1);
	}

	/* parse_identifier() modifies its first argument,
	 * returning pointers into it */
	identifier_copy = sstrdup (fields[1]);
