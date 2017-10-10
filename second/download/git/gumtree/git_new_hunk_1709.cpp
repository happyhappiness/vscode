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
