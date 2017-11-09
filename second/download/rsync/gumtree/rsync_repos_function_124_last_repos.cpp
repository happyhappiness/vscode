void parse_name_map(char *map, BOOL usernames)
{
	struct idlist **idmap_ptr = usernames ? &uidmap : &gidmap;
	struct idlist **idlist_ptr = usernames ? &uidlist : &gidlist;
	char *colon, *cp = map + strlen(map);
	union name_or_id noiu;
	id_t id1;
	uint16 flags;

	/* Parse the list in reverse, so the order in the struct is right. */
	while (1) {
		while (cp > map && cp[-1] != ',') cp--;
		if (!(colon = strchr(cp, ':'))) {
			rprintf(FERROR, "No colon found in --%smap: %s\n",
				usernames ? "user" : "group", cp);
			exit_cleanup(RERR_SYNTAX);
		}
		if (!colon[1]) {
			rprintf(FERROR, "No name found after colon --%smap: %s\n",
				usernames ? "user" : "group", cp);
			exit_cleanup(RERR_SYNTAX);
		}
		*colon = '\0';

		if (isDigit(cp)) {
			char *dash = strchr(cp, '-');
			if (strspn(cp, "0123456789-") != (size_t)(colon - cp)
			 || (dash && (!dash[1] || strchr(dash+1, '-')))) {
				rprintf(FERROR, "Invalid number in --%smap: %s\n",
					usernames ? "user" : "group", cp);
				exit_cleanup(RERR_SYNTAX);
			}
			if (dash) {
				*dash = '\0';
				noiu.max_id = id_parse(dash+1);
			} else
				noiu.max_id = 0;
			flags = 0;
			id1 = id_parse(cp);
			if (dash)
				*dash = '-';
		} else if (strpbrk(cp, "*[?")) {
			flags = NFLAGS_WILD_NAME_MATCH;
			noiu.name = cp;
			id1 = 0;
		} else {
			flags = NFLAGS_NAME_MATCH;
			noiu.name = cp;
			id1 = 0;
		}

		if (usernames) {
			uid_t uid;
			if (user_to_uid(colon+1, &uid, True))
				add_to_list(idmap_ptr, id1, noiu, uid, flags);
			else {
				rprintf(FERROR,
				    "Unknown --usermap name on receiver: %s\n",
				    colon+1);
			}
		} else {
			gid_t gid;
			if (group_to_gid(colon+1, &gid, True))
				add_to_list(idmap_ptr, id1, noiu, gid, flags);
			else {
				rprintf(FERROR,
				    "Unknown --groupmap name on receiver: %s\n",
				    colon+1);
			}
		}

		if (cp == map)
			break;

		*--cp = '\0'; /* replace comma */
	}

	/* The 0 user/group doesn't get its name sent, so add it explicitly. */
	recv_add_id(idlist_ptr, *idmap_ptr, 0,
		    numeric_ids ? NULL : usernames ? uid_to_user(0) : gid_to_group(0));
}