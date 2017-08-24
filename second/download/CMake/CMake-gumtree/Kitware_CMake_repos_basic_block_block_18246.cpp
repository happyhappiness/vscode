{
	if (!is_lclppb_valid(options))
		return true;

	*byte = (options->pb * 5 + options->lp) * 9 + options->lc;
	assert(*byte <= (4 * 5 + 4) * 9 + 8);

	return false;
}