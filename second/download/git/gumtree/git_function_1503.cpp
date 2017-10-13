static void populate_value(struct refinfo *ref)
{
	void *buf;
	struct object *obj;
	int eaten, i;
	unsigned long size;
	const unsigned char *tagged;

	ref->value = xcalloc(used_atom_cnt, sizeof(struct atom_value));

	if (need_symref && (ref->flag & REF_ISSYMREF) && !ref->symref) {
		unsigned char unused1[20];
		ref->symref = resolve_refdup(ref->refname, RESOLVE_REF_READING,
					     unused1, NULL);
		if (!ref->symref)
			ref->symref = "";
	}

	/* Fill in specials first */
	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i];
		struct atom_value *v = &ref->value[i];
		int deref = 0;
		const char *refname;
		const char *formatp;
		struct branch *branch = NULL;

		if (*name == '*') {
			deref = 1;
			name++;
		}

		if (starts_with(name, "refname"))
			refname = ref->refname;
		else if (starts_with(name, "symref"))
			refname = ref->symref ? ref->symref : "";
		else if (starts_with(name, "upstream")) {
			/* only local branches may have an upstream */
			if (!starts_with(ref->refname, "refs/heads/"))
				continue;
			branch = branch_get(ref->refname + 11);

			if (!branch || !branch->merge || !branch->merge[0] ||
			    !branch->merge[0]->dst)
				continue;
			refname = branch->merge[0]->dst;
		} else if (starts_with(name, "color:")) {
			char color[COLOR_MAXLEN] = "";

			if (color_parse(name + 6, color) < 0)
				die(_("unable to parse format"));
			v->s = xstrdup(color);
			continue;
		} else if (!strcmp(name, "flag")) {
			char buf[256], *cp = buf;
			if (ref->flag & REF_ISSYMREF)
				cp = copy_advance(cp, ",symref");
			if (ref->flag & REF_ISPACKED)
				cp = copy_advance(cp, ",packed");
			if (cp == buf)
				v->s = "";
			else {
				*cp = '\0';
				v->s = xstrdup(buf + 1);
			}
			continue;
		} else if (!deref && grab_objectname(name, ref->objectname, v)) {
			continue;
		} else if (!strcmp(name, "HEAD")) {
			const char *head;
			unsigned char sha1[20];

			head = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
						  sha1, NULL);
			if (!strcmp(ref->refname, head))
				v->s = "*";
			else
				v->s = " ";
			continue;
		} else
			continue;

		formatp = strchr(name, ':');
		if (formatp) {
			int num_ours, num_theirs;

			formatp++;
			if (!strcmp(formatp, "short"))
				refname = shorten_unambiguous_ref(refname,
						      warn_ambiguous_refs);
			else if (!strcmp(formatp, "track") &&
				 starts_with(name, "upstream")) {
				char buf[40];

				stat_tracking_info(branch, &num_ours, &num_theirs);
				if (!num_ours && !num_theirs)
					v->s = "";
				else if (!num_ours) {
					sprintf(buf, "[behind %d]", num_theirs);
					v->s = xstrdup(buf);
				} else if (!num_theirs) {
					sprintf(buf, "[ahead %d]", num_ours);
					v->s = xstrdup(buf);
				} else {
					sprintf(buf, "[ahead %d, behind %d]",
						num_ours, num_theirs);
					v->s = xstrdup(buf);
				}
				continue;
			} else if (!strcmp(formatp, "trackshort") &&
				   starts_with(name, "upstream")) {
				assert(branch);
				stat_tracking_info(branch, &num_ours, &num_theirs);
				if (!num_ours && !num_theirs)
					v->s = "=";
				else if (!num_ours)
					v->s = "<";
				else if (!num_theirs)
					v->s = ">";
				else
					v->s = "<>";
				continue;
			} else
				die("unknown %.*s format %s",
				    (int)(formatp - name), name, formatp);
		}

		if (!deref)
			v->s = refname;
		else {
			int len = strlen(refname);
			char *s = xmalloc(len + 4);
			sprintf(s, "%s^{}", refname);
			v->s = s;
		}
	}

	for (i = 0; i < used_atom_cnt; i++) {
		struct atom_value *v = &ref->value[i];
		if (v->s == NULL)
			goto need_obj;
	}
	return;

 need_obj:
	buf = get_obj(ref->objectname, &obj, &size, &eaten);
	if (!buf)
		die("missing object %s for %s",
		    sha1_to_hex(ref->objectname), ref->refname);
	if (!obj)
		die("parse_object_buffer failed on %s for %s",
		    sha1_to_hex(ref->objectname), ref->refname);

	grab_values(ref->value, 0, obj, buf, size);
	if (!eaten)
		free(buf);

	/*
	 * If there is no atom that wants to know about tagged
	 * object, we are done.
	 */
	if (!need_tagged || (obj->type != OBJ_TAG))
		return;

	/*
	 * If it is a tag object, see if we use a value that derefs
	 * the object, and if we do grab the object it refers to.
	 */
	tagged = ((struct tag *)obj)->tagged->sha1;

	/*
	 * NEEDSWORK: This derefs tag only once, which
	 * is good to deal with chains of trust, but
	 * is not consistent with what deref_tag() does
	 * which peels the onion to the core.
	 */
	buf = get_obj(tagged, &obj, &size, &eaten);
	if (!buf)
		die("missing object %s for %s",
		    sha1_to_hex(tagged), ref->refname);
	if (!obj)
		die("parse_object_buffer failed on %s for %s",
		    sha1_to_hex(tagged), ref->refname);
	grab_values(ref->value, 1, obj, buf, size);
	if (!eaten)
		free(buf);
}