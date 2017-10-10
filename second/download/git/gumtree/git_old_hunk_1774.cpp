	while (next < input.buf + input.len) {
		if (*next == line_termination)
			die("empty command in input");
		else if (isspace(*next))
			die("whitespace before command: %s", next);
		else if (starts_with(next, "update "))
			next = parse_cmd_update(&input, next + 7);
		else if (starts_with(next, "create "))
			next = parse_cmd_create(&input, next + 7);
		else if (starts_with(next, "delete "))
			next = parse_cmd_delete(&input, next + 7);
		else if (starts_with(next, "verify "))
			next = parse_cmd_verify(&input, next + 7);
		else if (starts_with(next, "option "))
			next = parse_cmd_option(&input, next + 7);
		else
			die("unknown command: %s", next);

		next++;
