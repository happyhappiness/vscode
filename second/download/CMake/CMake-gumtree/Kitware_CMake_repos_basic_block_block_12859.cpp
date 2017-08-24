(strcmp(value, "BINARY") == 0)
				/* Binary  mode. */
				tar->pax_hdrcharset_binary = 1;
			else if (strcmp(value, "ISO-IR 10646 2000 UTF-8") == 0)
				tar->pax_hdrcharset_binary = 0