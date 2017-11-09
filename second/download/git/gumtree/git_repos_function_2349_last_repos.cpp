void git_attr_set_direction(enum git_attr_direction new_direction,
			    struct index_state *istate)
{
	if (is_bare_repository() && new_direction != GIT_ATTR_INDEX)
		die("BUG: non-INDEX attr direction in a bare repo");

	if (new_direction != direction)
		drop_all_attr_stacks();

	direction = new_direction;
	use_index = istate;
}