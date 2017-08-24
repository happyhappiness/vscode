{
				as->length = p - as->s;
				if (archive_string_ensure(as,
				    as->buffer_length + len + 1) == NULL)
					return (-1);
				p = as->s + as->length;
				endp = as->s + as->buffer_length -1;
			}