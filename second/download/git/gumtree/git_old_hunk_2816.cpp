		error("no such remote ref %s", sought[i]->name);
		ret = 1;
	}

	while (ref) {
		printf("%s %s\n",
		       sha1_to_hex(ref->old_sha1), ref->name);
		ref = ref->next;
	}

	return ret;
}
