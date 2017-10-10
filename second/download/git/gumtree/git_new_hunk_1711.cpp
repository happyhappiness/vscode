		emit(cp, sp);
	}
	if (need_color_reset_at_eol) {
		struct atom_value resetv;
		char color[COLOR_MAXLEN] = "";

		if (color_parse("reset", color) < 0)
			die("BUG: couldn't parse 'reset' as a color");
		resetv.s = color;
		print_value(&resetv, quote_style);
	}
	putchar('\n');
}

