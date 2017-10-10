
		if (is_delta_type(obj->type))
			chain_histogram[obj_stat[i].delta_depth - 1]++;
		if (stat_only)
			continue;
		printf("%s %-6s %lu %lu %"PRIuMAX,
		       oid_to_hex(&obj->idx.oid),
		       typename(obj->real_type), obj->size,
		       (unsigned long)(obj[1].idx.offset - obj->idx.offset),
		       (uintmax_t)obj->idx.offset);
		if (is_delta_type(obj->type)) {
			struct object_entry *bobj = &objects[obj_stat[i].base_object_no];
			printf(" %u %s", obj_stat[i].delta_depth,
			       oid_to_hex(&bobj->idx.oid));
		}
		putchar('\n');
	}

	if (baseobjects)
		printf_ln(Q_("non delta: %d object",
