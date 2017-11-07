fprintf(opt->diffopt.file, "%s<%s>\n", (i > 0 ? "\t" : "References: "),
			       opt->ref_message_ids->items[i].string);