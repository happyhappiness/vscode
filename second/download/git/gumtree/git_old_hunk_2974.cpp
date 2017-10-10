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
