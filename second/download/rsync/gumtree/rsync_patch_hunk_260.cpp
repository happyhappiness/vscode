 char *map_ptr(struct map_struct *map,off_t offset,int len);
 void unmap_file(struct map_struct *map);
 int piped_child(char **command,int *f_in,int *f_out);
 void out_of_memory(char *str);
 int set_modtime(char *fname,time_t modtime);
 int set_blocking(int fd, int set);
+int create_directory_path(char *fname);
