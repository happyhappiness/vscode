		emit(cp, sp);
	}
	if (need_color_reset_at_eol) {
		struct atom_value resetv;
		char color[COLOR_MAXLEN] = "";

		color_parse("reset", "--format", color);
		resetv.s = color;
		print_value(&resetv, quote_style);
	}
	putchar('\n');
}

