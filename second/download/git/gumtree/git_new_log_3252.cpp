fprintf(opt->diffopt.file, " (from %s)",
			       find_unique_abbrev(parent->object.oid.hash,
						  abbrev_commit));