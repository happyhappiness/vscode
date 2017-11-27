static int config_add_writer (oconfig_item_t *ci,
		c_psql_writer_t *src_writers, size_t src_writers_num,
		c_psql_writer_t ***dst_writers, size_t *dst_writers_num)
{
	char *name;

	size_t i;

	if ((ci == NULL) || (dst_writers == NULL) || (dst_writers_num == NULL))
		return -1;

	if ((ci->values_num != 1)
			|| (ci->values[0].type != OCONFIG_TYPE_STRING)) {
		log_err ("`Writer' expects a single string argument.");
		return 1;
	}

	name = ci->values[0].value.string;

	for (i = 0; i < src_writers_num; ++i) {
		c_psql_writer_t **tmp;

		if (strcasecmp (name, src_writers[i].name) != 0)
			continue;

		tmp = realloc (*dst_writers,
				sizeof (**dst_writers) * (*dst_writers_num + 1));
		if (tmp == NULL) {
			log_err ("Out of memory.");
			return -1;
		}

		tmp[*dst_writers_num] = src_writers + i;

		*dst_writers = tmp;
		++(*dst_writers_num);
		break;
	}

	if (i >= src_writers_num) {
		log_err ("No such writer: `%s'", name);
		return -1;
	}

	return 0;
}