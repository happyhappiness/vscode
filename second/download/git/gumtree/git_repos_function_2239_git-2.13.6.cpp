static struct attr_stack *read_attr(const char *path, int macro_ok)
{
	struct attr_stack *res = NULL;

	if (direction == GIT_ATTR_INDEX) {
		res = read_attr_from_index(path, macro_ok);
	} else if (!is_bare_repository()) {
		if (direction == GIT_ATTR_CHECKOUT) {
			res = read_attr_from_index(path, macro_ok);
			if (!res)
				res = read_attr_from_file(path, macro_ok);
		} else if (direction == GIT_ATTR_CHECKIN) {
			res = read_attr_from_file(path, macro_ok);
			if (!res)
				/*
				 * There is no checked out .gitattributes file
				 * there, but we might have it in the index.
				 * We allow operation in a sparsely checked out
				 * work tree, so read from it.
				 */
				res = read_attr_from_index(path, macro_ok);
		}
	}

	if (!res)
		res = xcalloc(1, sizeof(*res));
	return res;
}