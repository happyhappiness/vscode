static void populate_value(struct ref_array_item *ref)
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
		const char *valp;
		struct branch *branch = NULL;

		v->handler = append_atom;

		if (*name == '*') {
			deref = 1;
			name++;
		}

		if (starts_with(name, "refname"))
			refname = ref->refname;
		else if (starts_with(name, "symref"))
			refname = ref->symref ? ref->symref : "";
		else if (starts_with(name, "upstream")) {
			const char *branch_name;
			/* only local branches may have an upstream */
			if (!skip_prefix(ref->refname, "refs/heads/",
					 &branch_name))
				continue;
			branch = branch_get(branch_name);

			refname = branch_get_upstream(branch, NULL);
			if (!refname)
				continue;
		} else if (starts_with(name, "push")) {
			const char *branch_name;
			if (!skip_prefix(ref->refname, "refs/heads/",
					 &branch_name))
				continue;
			branch = branch_get(branch_name);

			refname = branch_get_push(branch, NULL);
			if (!refname)
				continue;
		} else if (match_atom_name(name, "color", &valp)) {
			char color[COLOR_MAXLEN] = "";

			if (!valp)
				die(_("expected format: %%(color:<color>)"));
			if (color_parse(valp, color) < 0)
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
		} else if (match_atom_name(name, "align", &valp)) {
			struct align *align = &v->u.align;
			struct strbuf **s, **to_free;
			int width = -1;

			if (!valp)
				die(_("expected format: %%(align:<width>,<position>)"));

			/*
			 * TODO: Implement a function similar to strbuf_split_str()
			 * which would omit the separator from the end of each value.
			 */
			s = to_free = strbuf_split_str(valp, ',', 0);

			align->position = ALIGN_LEFT;

			while (*s) {
				/*  Strip trailing comma */
				if (s[1])
					strbuf_setlen(s[0], s[0]->len - 1);
				if (!strtoul_ui(s[0]->buf, 10, (unsigned int *)&width))
					;
				else if (!strcmp(s[0]->buf, "left"))
					align->position = ALIGN_LEFT;
				else if (!strcmp(s[0]->buf, "right"))
					align->position = ALIGN_RIGHT;
				else if (!strcmp(s[0]->buf, "middle"))
					align->position = ALIGN_MIDDLE;
				else
					die(_("improper format entered align:%s"), s[0]->buf);
				s++;
			}

			if (width < 0)
				die(_("positive width expected with the %%(align) atom"));
			align->width = width;
			strbuf_list_free(to_free);
			v->handler = align_atom_handler;
			continue;
		} else if (!strcmp(name, "end")) {
			v->handler = end_atom_handler;
			continue;
		} else
			continue;

		formatp = strchr(name, ':');
		if (formatp) {
			int num_ours, num_theirs;
			const char *arg;

			formatp++;
			if (!strcmp(formatp, "short"))
				refname = shorten_unambiguous_ref(refname,
						      warn_ambiguous_refs);
			else if (skip_prefix(formatp, "strip=", &arg))
				refname = strip_ref_components(refname, arg);
			else if (!strcmp(formatp, "track") &&
				 (starts_with(name, "upstream") ||
				  starts_with(name, "push"))) {

				if (stat_tracking_info(branch, &num_ours,
						       &num_theirs, NULL))
					continue;

				if (!num_ours && !num_theirs)
					v->s = "";
				else if (!num_ours)
					v->s = xstrfmt("[behind %d]", num_theirs);
				else if (!num_theirs)
					v->s = xstrfmt("[ahead %d]", num_ours);
				else
					v->s = xstrfmt("[ahead %d, behind %d]",
						       num_ours, num_theirs);
				continue;
			} else if (!strcmp(formatp, "trackshort") &&
				   (starts_with(name, "upstream") ||
				    starts_with(name, "push"))) {
				assert(branch);

				if (stat_tracking_info(branch, &num_ours,
							&num_theirs, NULL))
					continue;

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
		else
			v->s = xstrfmt("%s^{}", refname);
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
	tagged = ((struct tag *)obj)->tagged->oid.hash;

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