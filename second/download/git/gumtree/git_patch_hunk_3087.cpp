 	if (!S_ISREG(st.st_mode))
 		return -1;
 	size = xsize_t(st.st_size);
 	i = open(filename, O_RDONLY);
 	if (i < 0)
 		goto err_ret;
-	data = xmalloc(size + 1);
+	data = xmallocz(size);
 	if (st.st_size != read_in_full(i, data, size)) {
 		error(_("'%s': short read %s"), filename, strerror(errno));
 		close(i);
 		free(data);
 		return -1;
 	}
 	close(i);
-	data[size] = 0;
 
 	gs->buf = data;
 	gs->size = size;
 	return 0;
 }
 
