		error("no such remote ref %s", sought[i]->name);
		ret = 1;
	}

	while (ref) {
		printf("%s %s\n",
		       oid_to_hex(&ref->old_oid), ref->name);
		ref = ref->next;
	}

	return ret;
}
