off_t send_files(struct file_list *flist,int f_out,int f_in);
void generate_files(int f,struct file_list *flist,char *local_name,int f_recv);
void send_token(int f,int token,struct map_struct *buf,int offset,
		int n,int toklen);
int recv_token(int f,char **data);
void see_token(char *data, int toklen);
int num_waiting(int fd);
struct map_struct *map_file(int fd,off_t len);
char *map_ptr(struct map_struct *map,off_t offset,int len);
void unmap_file(struct map_struct *map);
int piped_child(char **command,int *f_in,int *f_out);
void out_of_memory(char *str);
int set_modtime(char *fname,time_t modtime);
int set_blocking(int fd, int set);
int create_directory_path(char *fname);
