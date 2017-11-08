static int same_token(struct trailer_item *a, struct trailer_item *b)
{
	size_t a_len = token_len_without_separator(a->token, strlen(a->token));
	size_t b_len = token_len_without_separator(b->token, strlen(b->token));
	size_t min_len = (a_len > b_len) ? b_len : a_len;

	return !strncasecmp(a->token, b->token, min_len);
}