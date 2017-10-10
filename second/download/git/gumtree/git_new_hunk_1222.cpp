		mi.use_scissors = 1;
		break;
	default:
		die("BUG: invalid value for state->scissors");
	}

	mi.input = xfopen(mail, "r");
	mi.output = xfopen(am_path(state, "info"), "w");
	if (mailinfo(&mi, am_path(state, "msg"), am_path(state, "patch")))
		die("could not parse patch");

	fclose(mi.input);
	fclose(mi.output);

