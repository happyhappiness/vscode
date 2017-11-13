fprintf(stderr, "%s in %s has negative refcnt %d\n",
				ent->suspect->path,
				oid_to_hex(&ent->suspect->commit->object.oid),
				ent->suspect->refcnt);