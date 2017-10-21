struct file_list *get_dirlist(char *dirname, int dlen, int flags);
int unchanged_attrs(const char *fname, struct file_struct *file, stat_x *sxp);
void itemize(const char *fnamecmp, struct file_struct *file, int ndx, int statret,
	     stat_x *sxp, int32 iflags, uchar fnamecmp_type,
	     const char *xname);
int unchanged_file(char *fn, struct file_struct *file, STRUCT_STAT *st);
int atomic_create(struct file_struct *file, char *fname, const char *lnk,
		  dev_t rdev, stat_x *sxp, int del_for_flag);
void check_for_finished_files(int itemizing, enum logcode code, int check_redo);
void generate_files(int f_out, const char *local_name);
struct hashtable *hashtable_create(int size, int key64);
void hashtable_destroy(struct hashtable *tbl);
void *hashtable_find(struct hashtable *tbl, int64 key, int allocate_if_missing);
void init_hard_links(void);
struct ht_int64_node *idev_find(int64 dev, int64 ino);
void idev_destroy(void);
void match_hard_links(struct file_list *flist);
int hard_link_check(struct file_struct *file, int ndx, char *fname,
		    int statret, stat_x *sxp, int itemizing,
		    enum logcode code);
int hard_link_one(struct file_struct *file, const char *fname,
		  const char *oldname, int terse);
void finish_hard_link(struct file_struct *file, const char *fname, int fin_ndx,
		      STRUCT_STAT *stp, int itemizing, enum logcode code,
		      int alt_dest);
int skip_hard_link(struct file_struct *file, struct file_list **flist_p);
void reduce_iobuf_size(xbuf *out, size_t new_size);
void restore_iobuf_size(xbuf *out);
void noop_io_until_death(void);
int send_msg(enum msgcode code, const char *buf, size_t len, int convert);
void send_msg_int(enum msgcode code, int num);
void io_set_sock_fds(int f_in, int f_out);
void set_io_timeout(int secs);
void increment_active_files(int ndx, int itemizing, enum logcode code);
int get_redo_num(void);
int get_hlink_num(void);
void start_filesfrom_forwarding(int fd);
int read_line(int fd, char *buf, size_t bufsiz, int flags);
void read_args(int f_in, char *mod_name, char *buf, size_t bufsiz, int rl_nulls,
	       char ***argv_p, int *argc_p, char **request_p);
BOOL io_start_buffering_out(int f_out);
BOOL io_start_buffering_in(int f_in);
void io_end_buffering_in(BOOL free_buffers);
void io_end_buffering_out(BOOL free_buffers);
void maybe_flush_socket(int important);
void maybe_send_keepalive(time_t now, int flags);
void start_flist_forward(int ndx);
void stop_flist_forward(void);
void wait_for_receiver(void);
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
void io_flush(int flush_it_all);
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
int read_line_old(int fd, char *buf, size_t bufsiz, int eof_ok);
void io_printf(int fd, const char *format, ...);
void io_start_multiplex_out(int fd);
void io_start_multiplex_in(int fd);
int io_end_multiplex_in(int mode);
int io_end_multiplex_out(int mode);
void start_write_batch(int fd);
void stop_write_batch(void);
char *lp_bind_address(void);
char *lp_motd_file(void);
char *lp_pid_file(void);
char *lp_socket_options(void);
int lp_listen_backlog(void);
int lp_rsync_port(void);
char *lp_auth_users(int module_id);
char *lp_charset(int module_id);
char *lp_comment(int module_id);
char *lp_dont_compress(int module_id);
char *lp_exclude(int module_id);
