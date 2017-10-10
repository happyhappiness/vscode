		strbuf_add(oi->typename, type_buf, type_len);
	/*
	 * Set type to 0 if its an unknown object and
	 * we're obtaining the type using '--allow-unknown-type'
	 * option.
	 */
	if ((flags & LOOKUP_UNKNOWN_OBJECT) && (type < 0))
		type = 0;
	else if (type < 0)
		die("invalid object type");
	if (oi->typep)
		*oi->typep = type;

