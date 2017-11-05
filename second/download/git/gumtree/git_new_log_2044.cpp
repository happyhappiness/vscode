die("cannot simplify commit %s (invalid %s)",
					    oid_to_hex(&commit->object.oid),
					    oid_to_hex(&p->object.oid));