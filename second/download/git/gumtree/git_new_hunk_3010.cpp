				 * (they are grandparents for us).
				 * IOW, we pretend this parent is a
				 * "root" commit.
				 */
				if (parse_commit(p) < 0)
					die("cannot simplify commit %s (invalid %s)",
					    oid_to_hex(&commit->object.oid),
					    oid_to_hex(&p->object.oid));
				p->parents = NULL;
			}
		/* fallthrough */
		case REV_TREE_OLD:
		case REV_TREE_DIFFERENT:
			if (relevant_commit(p))
				relevant_change = 1;
			else
				irrelevant_change = 1;
			continue;
		}
		die("bad tree compare for commit %s", oid_to_hex(&commit->object.oid));
	}

	/*
	 * TREESAME is straightforward for single-parent commits. For merge
	 * commits, it is most useful to define it so that "irrelevant"
	 * parents cannot make us !TREESAME - if we have any relevant
