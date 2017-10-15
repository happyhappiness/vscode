fprintf (fpout,
		 "Content-Type: message/external-body; access-type=x-mutt-deleted;\n"
		 "\texpiration=%s; length=" OFF_T_FMT "\n"
		 "\n", date + 5, part->length);