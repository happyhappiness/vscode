		mi.use_scissors = 1;
		break;
	default:
		die("BUG: invalid value for state->scissors");
	}

	mi.input = fopen(mail, "r");
	if (!mi.input)
		die("could not open input");
	mi.output = fopen(am_path(state, "info"), "w");
	if (!mi.output)
		die("could not open output 'info'");
	if (mailinfo(&mi, am_path(state, "msg"), am_path(state, "patch")))
		die("could not parse patch");

	fclose(mi.input);
	fclose(mi.output);

