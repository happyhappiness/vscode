fprintf(s->fp, "# branch.oid %s%c",
			(s->is_initial ? "(initial)" : sha1_to_hex(s->sha1_commit)),
			eol);