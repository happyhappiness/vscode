fprintf(cb->newlog, "%s %s %s %lu %+05d\t%s",
				oid_to_hex(ooid), oid_to_hex(noid),
				email, timestamp, tz, message);