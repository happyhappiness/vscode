
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
