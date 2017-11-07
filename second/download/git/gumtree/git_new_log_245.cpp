printf("%s%06o %s %d\t",
			       tag,
			       ce->ce_mode,
			       find_unique_abbrev(ce->oid.hash, abbrev),
			       ce_stage(ce));