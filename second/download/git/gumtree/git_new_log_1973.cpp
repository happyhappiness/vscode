die("unable to parse commit %s",
		    item ? oid_to_hex(&item->object.oid) : "(null)");