				strbuf_addch(sb, ',');
			strbuf_addstr(sb, pathspec_magic[i].name);
		}
	strbuf_addf(sb, ",prefix:%d)", prefixlen);
}

static inline int get_literal_global(void)
{
	static int literal = -1;

	if (literal < 0)
		literal = git_env_bool(GIT_LITERAL_PATHSPECS_ENVIRONMENT, 0);
