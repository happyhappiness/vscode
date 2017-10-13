fprintf(stderr, "%s in %s has negative refcnt %d\n",
				ent->suspect->path,
				sha1_to_hex(ent->suspect->commit->object.sha1),
				ent->suspect->refcnt);