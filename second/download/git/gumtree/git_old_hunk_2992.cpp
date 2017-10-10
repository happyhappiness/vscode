		if (data[i] == '\n') {
			if (mid - start != 40)
				die("%sinfo/refs not valid: is this a git repository?",
				    url.buf);
			data[i] = 0;
			ref_name = mid + 1;
			ref = xmalloc(sizeof(struct ref) +
				      strlen(ref_name) + 1);
			memset(ref, 0, sizeof(struct ref));
			strcpy(ref->name, ref_name);
			get_sha1_hex(start, ref->old_sha1);
			if (!refs)
				refs = ref;
			if (last_ref)
				last_ref->next = ref;
			last_ref = ref;
			start = NULL;
