struct file_list *get_dirlist(char *dirname, int dlen, int flags);
int unchanged_attrs(const char *fname, struct file_struct *file, stat_x *sxp);
void itemize(const char *fnamecmp, struct file_struct *file, int ndx, int statret,
	     stat_x *sxp, int32 iflags, uchar fnamecmp_type,
	     const char *xname);
int unchanged_file(char *fn, struct file_struct *file, STRUCT_STAT *st);
void check_for_finished_files(int itemizing, enum logcode code, int check_redo);
void generate_files(int f_out, const char *local_name);
struct hashtable *hashtable_create(int size, int key64);
void hashtable_destroy(struct hashtable *tbl);
void *hashtable_find(struct hashtable *tbl, int64 key, int allocate_if_missing);
void init_hard_links(void);
struct ht_int64_node *idev_find(int64 dev, int64 ino);
void idev_destroy(void);
void match_hard_links(struct file_list *flist);
int hard_link_check(struct file_struct *file, int ndx, const char *fname,
		    int statret, stat_x *sxp, int itemizing,
		    enum logcode code);
int hard_link_one(struct file_struct *file, const char *fname,
		  const char *oldname, int terse);
void finish_hard_link(struct file_struct *file, const char *fname, int fin_ndx,
		      STRUCT_STAT *stp, int itemizing, enum logcode code,
		      int alt_dest);
int skip_hard_link(struct file_struct *file, struct file_list **flist_p);
void io_set_sock_fds(int f_in, int f_out);
void set_io_timeout(int secs);
void set_msg_fd_in(int fd);
void set_msg_fd_out(int fd);
void increment_active_files(int ndx, int itemizing, enum logcode code);
int send_msg(enum msgcode code, const char *buf, int len, int convert);
void send_msg_int(enum msgcode code, int num);
void wait_for_receiver(void);
int get_redo_num(void);
int get_hlink_num(void);
void io_set_filesfrom_fds(int f_in, int f_out);
int read_line(int fd, char *buf, size_t bufsiz, int flags);
void read_args(int f_in, char *mod_name, char *buf, size_t bufsiz, int rl_nulls,
	       char ***argv_p, int *argc_p, char **request_p);
int io_start_buffering_out(int f_out);
int io_start_buffering_in(int f_in);
void io_end_buffering_in(void);
void io_end_buffering_out(void);
void maybe_flush_socket(int important);
void maybe_send_keepalive(void);
void start_flist_forward(int f_in);
void stop_flist_forward(void);
unsigned short read_shortint(int f);
int32 read_int(int f);
int32 read_varint(int f);
int64 read_varlong(int f, uchar min_bytes);
int64 read_longint(int f);
void read_buf(int f, char *buf, size_t len);
void read_sbuf(int f, char *buf, size_t len);
uchar read_byte(int f);
int read_vstring(int f, char *buf, int bufsize);
void read_sum_head(int f, struct sum_struct *sum);
void write_sum_head(int f, struct sum_struct *sum);
int io_flush(int flush_it_all);
void write_shortint(int f, unsigned short x);
void write_int(int f, int32 x);
void write_varint(int f, int32 x);
void write_varlong(int f, int64 x, uchar min_bytes);
void write_longint(int f, int64 x);
void write_buf(int f, const char *buf, size_t len);
void write_sbuf(int f, const char *buf);
void write_byte(int f, uchar c);
void write_vstring(int f, const char *str, int len);
void write_ndx(int f, int32 ndx);
int32 read_ndx(int f);
int read_line_old(int f, char *buf, size_t bufsiz);
void io_printf(int fd, const char *format, ...);
void io_start_multiplex_out(void);
void io_start_multiplex_in(void);
int io_multiplex_write(enum msgcode code, const char *buf, size_t len, int convert);
void io_end_multiplex_in(void);
void io_end_multiplex_out(void);
void start_write_batch(int fd);
void stop_write_batch(void);
char *lp_bind_address(void);
char *lp_motd_file(void);
char *lp_pid_file(void);
char *lp_socket_options(void);
int lp_rsync_port(void);
char *lp_auth_users(int module_id);
char *lp_charset(int module_id);
char *lp_comment(int module_id);
char *lp_dont_compress(int module_id);
char *lp_exclude(int module_id);
