static void dump_grep_pat(struct grep_pat *p)
{
	switch (p->token) {
	case GREP_AND: fprintf(stderr, "*and*"); break;
	case GREP_OPEN_PAREN: fprintf(stderr, "*(*"); break;
	case GREP_CLOSE_PAREN: fprintf(stderr, "*)*"); break;
	case GREP_NOT: fprintf(stderr, "*not*"); break;
	case GREP_OR: fprintf(stderr, "*or*"); break;

	case GREP_PATTERN: fprintf(stderr, "pattern"); break;
	case GREP_PATTERN_HEAD: fprintf(stderr, "pattern_head"); break;
	case GREP_PATTERN_BODY: fprintf(stderr, "pattern_body"); break;
	}

	switch (p->token) {
	default: break;
	case GREP_PATTERN_HEAD:
		fprintf(stderr, "<head %d>", p->field); break;
	case GREP_PATTERN_BODY:
		fprintf(stderr, "<body>"); break;
	}
	switch (p->token) {
	default: break;
	case GREP_PATTERN_HEAD:
	case GREP_PATTERN_BODY:
	case GREP_PATTERN:
		fprintf(stderr, "%.*s", (int)p->patternlen, p->pattern);
		break;
	}
	fputc('\n', stderr);
}