fprintf(cb->newlog, "%s %s %s %lu %+05d\t%s",
				sha1_to_hex(osha1), sha1_to_hex(nsha1),
				email, timestamp, tz, message);