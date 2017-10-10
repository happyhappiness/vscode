		} else if ((flag & REF_ISSYMREF) && strcmp(fullref, "HEAD")) {
			warning("ignoring dangling symref %s.", fullref);
		} else if ((flag & REF_ISBROKEN) && strchr(fullref, '/')) {
			warning("ignoring broken ref %s.", fullref);
		}
	}
	return refs_found;
}

int dwim_log(const char *str, int len, unsigned char *sha1, char **log)
{
	char *last_branch = substitute_branch_name(&str, &len);
