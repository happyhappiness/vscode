 	for (i = 0; i < 3; i++) {
 		const char *fname = prefix_filename(prefix, prefixlen, argv[i]);
 		if (!names[i])
 			names[i] = argv[i];
 		if (read_mmfile(mmfs + i, fname))
 			return -1;
-		if (mmfs[i].size > MAX_XDIFF_SIZE ||
-		    buffer_is_binary(mmfs[i].ptr, mmfs[i].size))
+		if (buffer_is_binary(mmfs[i].ptr, mmfs[i].size))
 			return error("Cannot merge binary files: %s",
 					argv[i]);
 	}
 
 	xmp.ancestor = names[1];
 	xmp.file1 = names[0];
