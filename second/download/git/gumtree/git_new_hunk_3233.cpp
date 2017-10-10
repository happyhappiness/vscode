				v->s = "";
			else {
				*cp = '\0';
				v->s = xstrdup(buf + 1);
			}
			continue;
		} else if (!deref && grab_objectname(name, ref->objectname, v, atom)) {
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
		} else if (starts_with(name, "align")) {
			v->u.align = atom->u.align;
			v->handler = align_atom_handler;
			continue;
		} else if (!strcmp(name, "end")) {
			v->handler = end_atom_handler;
			continue;
		} else
			continue;

		formatp = strchr(name, ':');
		if (formatp) {
			const char *arg;

			formatp++;
			if (!strcmp(formatp, "short"))
				refname = shorten_unambiguous_ref(refname,
						      warn_ambiguous_refs);
			else if (skip_prefix(formatp, "strip=", &arg))
				refname = strip_ref_components(refname, arg);
			else
				die(_("unknown %.*s format %s"),
				    (int)(formatp - name), name, formatp);
		}

		if (!deref)
			v->s = refname;
		else
