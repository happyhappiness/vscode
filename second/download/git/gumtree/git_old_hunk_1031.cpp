			*prefix_len = strtol(pos + 7, &endptr, 10);
			if (endptr - pos != len)
				die(_("invalid parameter for pathspec magic 'prefix'"));
			continue;
		}

		for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
			if (strlen(pathspec_magic[i].name) == len &&
			    !strncmp(pathspec_magic[i].name, pos, len)) {
				*magic |= pathspec_magic[i].bit;
				break;
			}
