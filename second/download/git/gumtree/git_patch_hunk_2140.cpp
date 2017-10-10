 			return error("insufficient permission for adding an object to repository database %s", get_object_directory());
 		else
 			return error("unable to create temporary file: %s", strerror(errno));
 	}
 
 	/* Set it up */
-	memset(&stream, 0, sizeof(stream));
 	git_deflate_init(&stream, zlib_compression_level);
 	stream.next_out = compressed;
 	stream.avail_out = sizeof(compressed);
 	git_SHA1_Init(&c);
 
 	/* First header.. */
