int start_inband_exchange(char *user, char *path, int f_in, int f_out, 
			  int argc);
int start_daemon(int f_in, int f_out);
int daemon_main(void);
void setup_protocol(int f_out,int f_in);
int claim_connection(char *fname,int max_connections);
void clear_exclude_list(struct exclude_list_struct *listp);
int check_exclude(struct exclude_list_struct *listp, char *name, int name_is_dir);
void add_exclude(struct exclude_list_struct *listp, const char *pattern,
		 int xflags);
void add_exclude_file(struct exclude_list_struct *listp, const char *fname,
		      int xflags);
void send_exclude_list(int f);
void recv_exclude_list(int f);
void add_cvs_excludes(void);
int sparse_end(int f);
int flush_write_file(int f);
int write_file(int f,char *buf,size_t len);
struct map_struct *map_file(int fd, OFF_T len, OFF_T map_size,
			    size_t block_size);
char *map_ptr(struct map_struct *map,OFF_T offset,int len);
int unmap_file(struct map_struct *map);
void init_flist(void);
void show_flist_stats(void);
int link_stat(const char *path, STRUCT_STAT *buffer, int follow_dirlinks);
void flist_expand(struct file_list *flist);
void send_file_entry(struct file_struct *file, int f, unsigned short base_flags);
void receive_file_entry(struct file_struct **fptr, unsigned short flags,
			struct file_list *flist, int f);
struct file_struct *make_file(char *fname, struct file_list *flist,
			      int exclude_level);
void send_file_name(int f, struct file_list *flist, char *fname,
		    int recursive, unsigned short base_flags);
struct file_list *send_file_list(int f, int argc, char *argv[]);
struct file_list *recv_file_list(int f);
int file_compare(struct file_struct **file1, struct file_struct **file2);
int flist_find(struct file_list *flist, struct file_struct *f);
void clear_file(int i, struct file_list *flist);
struct file_list *flist_new(int with_hlink, char *msg);
void flist_free(struct file_list *flist);
int f_name_cmp(struct file_struct *f1, struct file_struct *f2);
char *f_name_to(struct file_struct *f, char *fbuf);
char *f_name(struct file_struct *f);
void write_sum_head(int f, struct sum_struct *sum);
void generate_files(int f_out, struct file_list *flist, char *local_name);
void init_hard_links(struct file_list *flist);
int hard_link_check(struct file_struct *file, int skip);
void do_hard_links(void);
void io_set_sock_fds(int f_in, int f_out);
void set_msg_fd_in(int fd);
void set_msg_fd_out(int fd);
void send_msg(enum msgcode code, char *buf, int len);
int msg_list_push(int flush_it_all);
int get_redo_num(void);
void io_set_filesfrom_fds(int f_in, int f_out);
int read_filesfrom_line(int fd, char *fname);
void io_start_buffering_out(void);
void io_start_buffering_in(void);
void io_end_buffering(void);
int32 read_int(int f);
int64 read_longint(int f);
void read_buf(int f,char *buf,size_t len);
void read_sbuf(int f,char *buf,size_t len);
unsigned char read_byte(int f);
void io_flush(int flush_it_all);
void write_int(int f,int32 x);
void write_int_named(int f, int32 x, const char *phase);
void write_longint(int f, int64 x);
void write_buf(int f,char *buf,size_t len);
void write_sbuf(int f, char *buf);
void write_byte(int f,unsigned char c);
int read_line(int f, char *buf, size_t maxlen);
void io_printf(int fd, const char *format, ...);
void io_start_multiplex_out(void);
void io_start_multiplex_in(void);
int io_multiplex_write(enum msgcode code, char *buf, size_t len);
void close_multiplexing_in(void);
