			if (head && !strcmp(ref->refname, head))
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
			v->s = xstrfmt("%s^{}", refname);
	}

