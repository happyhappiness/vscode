void write_flush(int f);
int readfd(int fd,char *buffer,int N);
int read_int(int f);
void read_buf(int f,char *buf,int len);
char *map_file(int fd,off_t len);
void unmap_file(char *buf,off_t len);
int piped_child(char **command,int *f_in,int *f_out);
void out_of_memory(char *str);
