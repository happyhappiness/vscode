{
		*offset = lha->entry_offset;
		*size = 0;
		*buff = NULL;
		return (lha_end_of_entry(a));
	}