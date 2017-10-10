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
