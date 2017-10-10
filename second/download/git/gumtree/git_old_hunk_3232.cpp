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
