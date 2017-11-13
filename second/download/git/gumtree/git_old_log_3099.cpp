printf("M %06o %s ", spec->mode,
				       sha1_to_hex(anonymize ?
						   anonymize_sha1(spec->sha1) :
						   spec->sha1));