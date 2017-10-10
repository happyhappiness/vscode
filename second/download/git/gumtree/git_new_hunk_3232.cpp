			if (!skip_prefix(ref->refname, "refs/heads/",
					 &branch_name))
				continue;
			branch = branch_get(branch_name);

			refname = branch_get_upstream(branch, NULL);
			if (refname)
				fill_remote_ref_details(atom, refname, branch, &v->s);
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
			fill_remote_ref_details(atom, refname, branch, &v->s);
			continue;
		} else if (starts_with(name, "color:")) {
			v->s = atom->u.color;
			continue;
		} else if (!strcmp(name, "flag")) {
			char buf[256], *cp = buf;
			if (ref->flag & REF_ISSYMREF)
				cp = copy_advance(cp, ",symref");
			if (ref->flag & REF_ISPACKED)
