{
			/* There is not enough output buffer so
			 * we have to expand it. */
			as->length = p - as->s;
			if (archive_string_ensure(as,
			    as->buffer_length + len * tm + ts) == NULL)
				return (-1);
			p = as->s + as->length;
			endp = as->s + as->buffer_length - ts;
		}