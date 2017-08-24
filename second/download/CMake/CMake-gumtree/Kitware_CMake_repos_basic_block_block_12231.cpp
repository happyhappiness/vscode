(*p != '/') {
			r = process_add_entry(a, mtree, &global, p, len,
			    &last_entry, is_form_d);
		} else if (len > 4 && strncmp(p, "/set", 4) == 0) {
			if (p[4] != ' ' && p[4] != '\t')
				break;
			r = process_global_set(a, &global, p);
		} else if (len > 6 && strncmp(p, "/unset", 6) == 0) {
			if (p[6] != ' ' && p[6] != '\t')
				break;
			r = process_global_unset(a, &global, p);
		} else
			break;