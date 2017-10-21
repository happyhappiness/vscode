    read(). It gives sliding window access to a file. mmap() is not
    used because of the possibility of another program (such as a
    mailer) truncating the file thus giving us a SIGBUS */
 struct map_struct *map_file(int fd,OFF_T len)
 {
 	struct map_struct *map;
-	map = (struct map_struct *)malloc(sizeof(*map));
+	map = new(struct map_struct);
 	if (!map) out_of_memory("map_file");
 
 	map->fd = fd;
 	map->file_size = len;
 	map->p = NULL;
 	map->p_size = 0;
