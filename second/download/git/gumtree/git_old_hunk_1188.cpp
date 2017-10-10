			if (second[len] == '\n' && !strncmp(name, second, len))
				return xmemdupz(name, len);
		}
	}
}

/* Verify that we recognize the lines following a git header */
static int parse_git_header(struct apply_state *state,
			    const char *line,
			    int len,
			    unsigned int size,
			    struct patch *patch)
