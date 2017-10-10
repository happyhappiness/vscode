			if (head && !strcmp(ref->refname, head))
				v->s = "*";
			else
				v->s = " ";
			continue;
		} else if (starts_with(name, "align")) {
			v->handler = align_atom_handler;
			continue;
		} else if (!strcmp(name, "end")) {
			v->handler = end_atom_handler;
			continue;
		} else if (starts_with(name, "if")) {
			const char *s;

			if (skip_prefix(name, "if:", &s))
				v->s = xstrdup(s);
			v->handler = if_atom_handler;
			continue;
		} else if (!strcmp(name, "then")) {
			v->handler = then_atom_handler;
			continue;
		} else if (!strcmp(name, "else")) {
			v->handler = else_atom_handler;
			continue;
		} else
			continue;

		if (!deref)
			v->s = refname;
		else
			v->s = xstrfmt("%s^{}", refname);
	}

