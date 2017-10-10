 		OPT_END(),
 	};
 
 	memset(&array, 0, sizeof(array));
 	memset(&filter, 0, sizeof(filter));
 
+	format.format = "%(objectname) %(objecttype)\t%(refname)";
+
+	git_config(git_default_config, NULL);
+
 	parse_options(argc, argv, prefix, opts, for_each_ref_usage, 0);
 	if (maxcount < 0) {
 		error("invalid --count argument: `%d'", maxcount);
 		usage_with_options(for_each_ref_usage, opts);
 	}
-	if (HAS_MULTI_BITS(quote_style)) {
+	if (HAS_MULTI_BITS(format.quote_style)) {
 		error("more than one quoting style?");
 		usage_with_options(for_each_ref_usage, opts);
 	}
-	if (verify_ref_format(format))
+	if (verify_ref_format(&format))
 		usage_with_options(for_each_ref_usage, opts);
 
 	if (!sorting)
 		sorting = ref_default_sorting();
 	sorting->ignore_case = icase;
 	filter.ignore_case = icase;
 
-	/* for warn_ambiguous_refs */
-	git_config(git_default_config, NULL);
-
 	filter.name_patterns = argv;
 	filter.match_as_path = 1;
 	filter_refs(&array, &filter, FILTER_REFS_ALL | FILTER_REFS_INCLUDE_BROKEN);
 	ref_array_sort(sorting, &array);
 
 	if (!maxcount || array.nr < maxcount)
 		maxcount = array.nr;
 	for (i = 0; i < maxcount; i++)
-		show_ref_array_item(array.items[i], format, quote_style);
+		show_ref_array_item(array.items[i], &format);
 	ref_array_clear(&array);
 	return 0;
 }
