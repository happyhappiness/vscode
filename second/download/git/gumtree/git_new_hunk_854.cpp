			return error_errno(_("could not open '%s' for reading"),
					   *paths);

		mail = mkpath("%s/%0*d", state->dir, state->prec, i + 1);

		out = fopen(mail, "w");
		if (!out) {
			if (in != stdin)
				fclose(in);
			return error_errno(_("could not open '%s' for writing"),
					   mail);
		}

		ret = fn(out, in, keep_cr);

		fclose(out);
		if (in != stdin)
			fclose(in);

		if (ret)
			return error(_("could not parse patch '%s'"), *paths);
	}

	state->cur = 1;
