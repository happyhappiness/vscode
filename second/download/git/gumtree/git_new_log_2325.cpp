fprintf(stderr,
				_("more than %i tags found; listed %i most recent\n"
				"gave up search at %s\n"),
				max_candidates, max_candidates,
				oid_to_hex(&gave_up_on->object.oid));