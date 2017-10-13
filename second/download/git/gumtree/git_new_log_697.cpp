fprintf(o, "%s%06o %s %d\t%s\n",
			label,
			ce->ce_mode,
			oid_to_hex(&ce->oid),
			ce_stage(ce),
			ce->name);