 int delete_file(char *fname);
 int set_perms(char *fname,struct file_struct *file,STRUCT_STAT *st,
 	      int report);
 void sig_int(void);
 void finish_transfer(char *fname, char *fnametmp, struct file_struct *file);
 void send_files(struct file_list *flist,int f_out,int f_in);
-int open_socket_out(char *host, int port, struct in_addr *address);
+int open_socket_out(char *host, int port, const char *bind_address,
+		    int af_hint);
+int open_socket_out_wrapped (char *host,
+			     int port,
+			     const char *bind_address,
+			     int af_hint);
 int is_a_socket(int fd);
 void start_accept_loop(int port, int (*fn)(int ));
 void set_socket_options(int fd, char *options);
 void become_daemon(void);
 char *client_addr(int fd);
 char *client_name(int fd);
-struct in_addr *ip_address(const char *str);
+int sock_exec(const char *prog);
 int do_unlink(char *fname);
 int do_symlink(char *fname1, char *fname2);
 int do_link(char *fname1, char *fname2);
 int do_lchown(const char *path, uid_t owner, gid_t group);
 int do_mknod(char *pathname, mode_t mode, dev_t dev);
 int do_rmdir(char *pathname);
 int do_open(char *pathname, int flags, mode_t mode);
 int do_chmod(const char *path, mode_t mode);
 int do_rename(char *fname1, char *fname2);
 int do_mkdir(char *fname, mode_t mode);
-char *do_mktemp(char *template);
+int do_mkstemp(char *template, mode_t perms);
 int do_stat(const char *fname, STRUCT_STAT *st);
 int do_lstat(const char *fname, STRUCT_STAT *st);
 int do_fstat(int fd, STRUCT_STAT *st);
 OFF_T do_lseek(int fd, OFF_T offset, int whence);
 void *do_mmap(void *start, int len, int prot, int flags, int fd, OFF_T offset);
 char *d_name(struct dirent *di);
+int main (int argc, char *argv[]);
 void set_compression(char *fname);
 void send_token(int f,int token,struct map_struct *buf,OFF_T offset,
 		int n,int toklen);
 int recv_token(int f,char **data);
 void see_token(char *data, int toklen);
 void add_uid(uid_t uid);
 void add_gid(gid_t gid);
 void send_uid_list(int f);
 void recv_uid_list(int f, struct file_list *flist);
 void set_nonblocking(int fd);
 void set_blocking(int fd);
 int fd_pair(int fd[2]);
-int piped_child(char **command,int *f_in,int *f_out);
-int local_child(int argc, char **argv,int *f_in,int *f_out);
+pid_t piped_child(char **command,int *f_in,int *f_out);
+pid_t local_child(int argc, char **argv,int *f_in,int *f_out);
 void out_of_memory(char *str);
 void overflow(char *str);
 int set_modtime(char *fname,time_t modtime);
 int create_directory_path(char *fname);
 int copy_file(char *source, char *dest, mode_t mode);
 int robust_unlink(char *fname);
