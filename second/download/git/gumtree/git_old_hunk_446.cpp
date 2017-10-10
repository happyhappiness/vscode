
		if (extra_have && !strcmp(name, ".have")) {
			sha1_array_append(extra_have, old_oid.hash);
			continue;
		}

		if (!check_ref(name, flags))
			continue;
		ref = alloc_ref(buffer + GIT_SHA1_HEXSZ + 1);
		oidcpy(&ref->old_oid, &old_oid);
		*list = ref;
		list = &ref->next;
		got_at_least_one_head = 1;
	}

	annotate_refs_with_symref_info(*orig_list);

	return list;
}
