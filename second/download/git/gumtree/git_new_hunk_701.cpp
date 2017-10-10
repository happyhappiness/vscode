			if (len > reflen)
				continue;
			if (memcmp(m, refname + reflen - len, len))
				continue;
			if (len == reflen)
				goto match;
			if (refname[reflen - len - 1] == '/')
				goto match;
		}
		return 0;
	}

match:
	found_match++;

	show_one(refname, oid);

	return 0;
}

static int add_existing(const char *refname, const struct object_id *oid,
			int flag, void *cbdata)
{
