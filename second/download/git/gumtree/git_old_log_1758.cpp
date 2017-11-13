fprintf(cb->newlog, "%s %s %s %lu %c%04d\t%s",
			sha1_to_hex(osha1), sha1_to_hex(nsha1),
			email, timestamp, sign, zone,
			message);