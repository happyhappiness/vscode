		return is_shallow;
	}
	stat_validity_update(&shallow_stat, fileno(fp));
	is_shallow = 1;

	while (fgets(buf, sizeof(buf), fp)) {
		struct object_id oid;
		if (get_oid_hex(buf, &oid))
			die("bad shallow line: %s", buf);
		register_shallow(&oid);
	}
	fclose(fp);
	return is_shallow;
}

struct commit_list *get_shallow_commits(struct object_array *heads, int depth,
