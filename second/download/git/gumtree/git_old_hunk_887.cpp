	}

	if (!match_cnt) {
		struct object_id *oid = &cmit->object.oid;
		if (always) {
			printf("%s", find_unique_abbrev(oid->hash, abbrev));
			if (dirty)
				printf("%s", dirty);
			printf("\n");
			return;
		}
		if (unannotated_cnt)
			die(_("No annotated tags can describe '%s'.\n"
			    "However, there were unannotated tags: try --tags."),
