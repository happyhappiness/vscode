static void added_object(unsigned nr, enum object_type type,
			 void *data, unsigned long size)
{
	struct delta_info **p = &delta_list;
	struct delta_info *info;

	while ((info = *p) != NULL) {
		if (!oidcmp(&info->base_oid, &obj_list[nr].oid) ||
		    info->base_offset == obj_list[nr].offset) {
			*p = info->next;
			p = &delta_list;
			resolve_delta(info->nr, type, data, size,
				      info->delta, info->size);
			free(info);
			continue;
		}
		p = &info->next;
	}
}