		char buf[32];
		if (opt->pathname) {
			output_color(opt, gs->name, strlen(gs->name),
				     opt->color_filename);
			output_sep(opt, ':');
		}
		xsnprintf(buf, sizeof(buf), "%u\n", count);
		opt->output(opt, buf, strlen(buf));
		return 1;
	}
	return !!last_hit;
}

