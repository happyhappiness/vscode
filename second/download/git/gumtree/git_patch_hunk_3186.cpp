 			else
 				error("unknown switch '%c'", *ctx.opt);
 			usage_with_options(update_index_usage, options);
 		}
 	}
 	argc = parse_options_end(&ctx);
+
+	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
 	if (preferred_index_format) {
 		if (preferred_index_format < INDEX_FORMAT_LB ||
 		    INDEX_FORMAT_UB < preferred_index_format)
 			die("index-version %d not in range: %d..%d",
 			    preferred_index_format,
 			    INDEX_FORMAT_LB, INDEX_FORMAT_UB);
