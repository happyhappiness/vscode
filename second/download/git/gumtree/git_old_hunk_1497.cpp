		return parse_long_magic(magic, prefix_len, item, elem);
	else
		/* shorthand */
		return parse_short_magic(magic, elem);
}

static void strip_submodule_slash_cheap(struct pathspec_item *item)
{
	if (item->len >= 1 && item->match[item->len - 1] == '/') {
		int i = cache_name_pos(item->match, item->len - 1);

		if (i >= 0 && S_ISGITLINK(active_cache[i]->ce_mode)) {
			item->len--;
			item->match[item->len] = '\0';
		}
	}
}

static void strip_submodule_slash_expensive(struct pathspec_item *item)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
		int ce_len = ce_namelen(ce);

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		if (item->len <= ce_len || item->match[ce_len] != '/' ||
		    memcmp(ce->name, item->match, ce_len))
			continue;

		if (item->len == ce_len + 1) {
			/* strip trailing slash */
			item->len--;
			item->match[item->len] = '\0';
		} else {
			die(_("Pathspec '%s' is in submodule '%.*s'"),
			    item->original, ce_len, ce->name);
		}
	}
}

static void die_inside_submodule_path(struct pathspec_item *item)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];
		int ce_len = ce_namelen(ce);

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		if (item->len < ce_len ||
		    !(item->match[ce_len] == '/' || item->match[ce_len] == '\0') ||
		    memcmp(ce->name, item->match, ce_len))
			continue;

		die(_("Pathspec '%s' is in submodule '%.*s'"),
		    item->original, ce_len, ce->name);
	}
}

/*
 * Perform the initialization of a pathspec_item based on a pathspec element.
 */
static void init_pathspec_item(struct pathspec_item *item, unsigned flags,
			       const char *prefix, int prefixlen,
			       const char *elt)
