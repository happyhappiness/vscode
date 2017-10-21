 	/* in most cases the region will already be available */
 	if (offset >= map->p_offset &&
 	    offset+len <= map->p_offset+map->p_len) {
 		return (map->p + (offset - map->p_offset));
 	}
 
-
 	/* nope, we are going to have to do a read. Work out our desired window */
-	if (offset > 2*CHUNK_SIZE) {
-		window_start = offset - 2*CHUNK_SIZE;
-		window_start &= ~((OFF_T)(CHUNK_SIZE-1)); /* assumes power of 2 */
-	} else {
-		window_start = 0;
-	}
-	window_size = MAX_MAP_SIZE;
+	window_start = offset;
+	window_size = map->def_window_size;
 	if (window_start + window_size > map->file_size) {
 		window_size = map->file_size - window_start;
 	}
 	if (offset + len > window_start + window_size) {
 		window_size = (offset+len) - window_start;
 	}
 
 	/* make sure we have allocated enough memory for the window */
 	if (window_size > map->p_size) {
 		map->p = realloc_array(map->p, char, window_size);
-		if (!map->p) out_of_memory("map_ptr");
+		if (!map->p)
+			out_of_memory("map_ptr");
 		map->p_size = window_size;
 	}
 
 	/* now try to avoid re-reading any bytes by reusing any bytes from the previous
 	   buffer. */
 	if (window_start >= map->p_offset &&
