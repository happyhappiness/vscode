int credential_match(const struct credential *want,
		     const struct credential *have)
{
#define CHECK(x) (!want->x || (have->x && !strcmp(want->x, have->x)))
	return CHECK(protocol) &&
	       CHECK(host) &&
	       CHECK(path) &&
	       CHECK(username);
#undef CHECK
}