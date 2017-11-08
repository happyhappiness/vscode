static int compare_and_swap_type(signed char *type,
				 enum object_type want,
				 enum object_type set)
{
	enum object_type old;

	type_cas_lock();
	old = *type;
	if (old == want)
		*type = set;
	type_cas_unlock();

	return old == want;
}