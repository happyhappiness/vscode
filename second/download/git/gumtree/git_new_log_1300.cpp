printf("%s %-6s %lu %lu %"PRIuMAX,
		       oid_to_hex(&obj->idx.oid),
		       typename(obj->real_type), obj->size,
		       (unsigned long)(obj[1].idx.offset - obj->idx.offset),
		       (uintmax_t)obj->idx.offset);