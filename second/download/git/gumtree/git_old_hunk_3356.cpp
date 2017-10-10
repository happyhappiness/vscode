			num += (ret - nr);
			nr = ret;
			continue;
		}

		if (stat(arg, &argstat) == -1) {
			error("cannot stat %s (%s)", arg, strerror(errno));
			return 1;
		}

		if (S_ISDIR(argstat.st_mode))
			ret = split_maildir(arg, dir, nr_prec, nr);
		else
