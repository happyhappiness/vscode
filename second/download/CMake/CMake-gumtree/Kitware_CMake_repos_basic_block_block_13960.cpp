{
					as->length = outp - as->s;
					bs = as->buffer_length +
					    (remaining * to_size) + rbytes;
					if (NULL ==
					    archive_string_ensure(as, bs))
						return (-1);
					outp = as->s + as->length;
					avail = as->buffer_length
					    - as->length - to_size;
				}