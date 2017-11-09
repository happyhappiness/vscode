void attr_check_free(struct attr_check *check)
{
	if (check) {
		/* Remove check from the check vector */
		check_vector_remove(check);

		attr_check_clear(check);
		free(check);
	}
}