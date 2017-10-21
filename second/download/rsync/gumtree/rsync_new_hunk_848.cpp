			gidset[ngroups++] = mygid;
		if (verbose > 3) {
			int pos;
			char *gidbuf = new_array(char, ngroups*21+32);
			if (!gidbuf)
				out_of_memory("is_in_group");
			pos = snprintf(gidbuf, 32, "process has %d gid%s: ",
				       ngroups, ngroups == 1? "" : "s");
			for (n = 0; n < ngroups; n++) {
				pos += snprintf(gidbuf+pos, 21, " %d", (int)gidset[n]);
			}
			rprintf(FINFO, "%s\n", gidbuf);
			free(gidbuf);
		}
	}

