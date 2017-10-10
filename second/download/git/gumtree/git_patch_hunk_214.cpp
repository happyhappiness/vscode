 		return istate->cache_nr;
 
 	istate->timestamp.sec = 0;
 	istate->timestamp.nsec = 0;
 	fd = open(path, O_RDONLY);
 	if (fd < 0) {
-		if (errno == ENOENT)
+		if (!must_exist && errno == ENOENT)
 			return 0;
-		die_errno("index file open failed");
+		die_errno("%s: index file open failed", path);
 	}
 
 	if (fstat(fd, &st))
 		die_errno("cannot stat the open index");
 
 	mmap_size = xsize_t(st.st_size);
