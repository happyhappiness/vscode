 			    int32 blk_size);
 char *map_ptr(struct map_struct *map, OFF_T offset, int32 len);
 int unmap_file(struct map_struct *map);
 void init_flist(void);
 void show_flist_stats(void);
 int link_stat(const char *path, STRUCT_STAT *stp, int follow_dirlinks);
-void flist_expand(struct file_list *flist);
-struct file_struct *make_file(char *fname, struct file_list *flist,
-			      STRUCT_STAT *stp, unsigned short flags,
-			      int filter_level);
+int push_pathname(const char *dir, int len);
+struct file_struct *make_file(const char *fname, struct file_list *flist,
+			      STRUCT_STAT *stp, int flags, int filter_level);
+void unmake_file(struct file_struct *file);
+void send_extra_file_list(int f, int at_least);
 struct file_list *send_file_list(int f, int argc, char *argv[]);
 struct file_list *recv_file_list(int f);
+void recv_additional_file_list(int f);
 int flist_find(struct file_list *flist, struct file_struct *f);
-void clear_file(struct file_struct *file, struct file_list *flist);
-struct file_list *flist_new(int with_hlink, char *msg);
+void clear_file(struct file_struct *file);
+struct file_list *flist_new(int flags, char *msg);
 void flist_free(struct file_list *flist);
-int f_name_cmp(struct file_struct *f1, struct file_struct *f2);
-char *f_name(struct file_struct *f, char *fbuf);
-struct file_list *get_dirlist(char *dirname, int dlen,
-			      int ignore_filter_rules);
-int unchanged_attrs(struct file_struct *file, STRUCT_STAT *st);
-void itemize(struct file_struct *file, int ndx, int statret, STRUCT_STAT *st,
-	     int32 iflags, uchar fnamecmp_type, char *xname);
+int f_name_cmp(const struct file_struct *f1, const struct file_struct *f2);
+int f_name_has_prefix(const struct file_struct *f1, const struct file_struct *f2);
+char *f_name_buf(void);
+char *f_name(const struct file_struct *f, char *fbuf);
+struct file_list *get_dirlist(char *dirname, int dlen, int ignore_filter_rules);
+int unchanged_attrs(const char *fname, struct file_struct *file, stat_x *sxp);
+void itemize(const char *fnamecmp, struct file_struct *file, int ndx, int statret,
+	     stat_x *sxp, int32 iflags, uchar fnamecmp_type,
+	     const char *xname);
 int unchanged_file(char *fn, struct file_struct *file, STRUCT_STAT *st);
-void check_for_finished_hlinks(int itemizing, enum logcode code);
-void generate_files(int f_out, struct file_list *flist, char *local_name);
+void check_for_finished_files(int itemizing, enum logcode code, int check_redo);
+void generate_files(int f_out, const char *local_name);
+struct hashtable *hashtable_create(int size, int key64);
+void hashtable_destroy(struct hashtable *tbl);
+void *hashtable_find(struct hashtable *tbl, int64 key, int allocate_if_missing);
 void init_hard_links(void);
-int hard_link_check(struct file_struct *file, int ndx, char *fname,
-		    int statret, STRUCT_STAT *st, int itemizing,
-		    enum logcode code, int skip);
-int hard_link_one(struct file_struct *file, int ndx, char *fname,
-		  int statret, STRUCT_STAT *st, char *toname, int terse,
-		  int itemizing, enum logcode code);
-void hard_link_cluster(struct file_struct *file, int master, int itemizing,
-		       enum logcode code);
+struct ht_int64_node *idev_find(int64 dev, int64 ino);
+void idev_destroy(void);
+void match_hard_links(struct file_list *flist);
+int hard_link_check(struct file_struct *file, int ndx, const char *fname,
+		    int statret, stat_x *sxp, int itemizing,
+		    enum logcode code);
+int hard_link_one(struct file_struct *file, const char *fname,
+		  const char *oldname, int terse);
+void finish_hard_link(struct file_struct *file, const char *fname, int fin_ndx,
+		      STRUCT_STAT *stp, int itemizing, enum logcode code,
+		      int alt_dest);
 void io_set_sock_fds(int f_in, int f_out);
 void set_io_timeout(int secs);
 void set_msg_fd_in(int fd);
 void set_msg_fd_out(int fd);
 void increment_active_files(int ndx, int itemizing, enum logcode code);
-void decrement_active_files(int ndx);
-int send_msg(enum msgcode code, char *buf, int len);
-int get_redo_num(int itemizing, enum logcode code);
+int send_msg(enum msgcode code, const char *buf, int len, int convert);
+void send_msg_int(enum msgcode code, int num);
+void wait_for_receiver(void);
+int get_redo_num(void);
 int get_hlink_num(void);
 void io_set_filesfrom_fds(int f_in, int f_out);
-int read_filesfrom_line(int fd, char *fname);
-void io_start_buffering_out(void);
-void io_start_buffering_in(void);
-void io_end_buffering(void);
-void maybe_flush_socket(void);
+int read_line(int fd, char *buf, size_t bufsiz, int flags);
+int read_args(int f_in, char *mod_name, char *buf, size_t bufsiz, int rl_nulls,
+	      char ***argv_p, int *argc_p, char **request_p);
+int io_start_buffering_out(int f_out);
+int io_start_buffering_in(int f_in);
+void io_end_buffering_in(void);
+void io_end_buffering_out(void);
+void maybe_flush_socket(int important);
 void maybe_send_keepalive(void);
-int read_shortint(int f);
+void start_flist_forward(int f_in);
+void stop_flist_forward();
+unsigned short read_shortint(int f);
 int32 read_int(int f);
+int32 read_varint(int f);
+int64 read_varlong(int f, uchar min_bytes);
 int64 read_longint(int f);
-void read_buf(int f,char *buf,size_t len);
-void read_sbuf(int f,char *buf,size_t len);
+void read_buf(int f, char *buf, size_t len);
+void read_sbuf(int f, char *buf, size_t len);
 uchar read_byte(int f);
 int read_vstring(int f, char *buf, int bufsize);
 void read_sum_head(int f, struct sum_struct *sum);
 void write_sum_head(int f, struct sum_struct *sum);
 void io_flush(int flush_it_all);
-void write_shortint(int f, int x);
-void write_int(int f,int32 x);
+void write_shortint(int f, unsigned short x);
+void write_int(int f, int32 x);
+void write_varint(int f, int32 x);
+void write_varlong(int f, int64 x, uchar min_bytes);
 void write_longint(int f, int64 x);
-void write_buf(int f,char *buf,size_t len);
-void write_sbuf(int f, char *buf);
+void write_buf(int f, const char *buf, size_t len);
+void write_sbuf(int f, const char *buf);
 void write_byte(int f, uchar c);
-void write_vstring(int f, char *str, int len);
-int read_line(int f, char *buf, size_t maxlen);
+void write_vstring(int f, const char *str, int len);
+void write_ndx(int f, int32 ndx);
+int32 read_ndx(int f);
+int read_line_old(int f, char *buf, size_t bufsiz);
 void io_printf(int fd, const char *format, ...);
 void io_start_multiplex_out(void);
 void io_start_multiplex_in(void);
-int io_multiplex_write(enum msgcode code, char *buf, size_t len);
-void close_multiplexing_in(void);
-void close_multiplexing_out(void);
+int io_multiplex_write(enum msgcode code, const char *buf, size_t len, int convert);
+void io_end_multiplex_in(void);
+void io_end_multiplex_out(void);
 void start_write_batch(int fd);
 void stop_write_batch(void);
 char *lp_bind_address(void);
 char *lp_motd_file(void);
 char *lp_pid_file(void);
 char *lp_socket_options(void);
 int lp_rsync_port(void);
-char *lp_auth_users(int );
-char *lp_comment(int );
-char *lp_dont_compress(int );
-char *lp_exclude(int );
-char *lp_exclude_from(int );
-char *lp_filter(int );
-char *lp_gid(int );
-char *lp_hosts_allow(int );
-char *lp_hosts_deny(int );
-char *lp_include(int );
-char *lp_include_from(int );
-char *lp_incoming_chmod(int );
-char *lp_lock_file(int );
-char *lp_log_file(int );
-char *lp_log_format(int );
-char *lp_name(int );
-char *lp_outgoing_chmod(int );
-char *lp_path(int );
-char *lp_postxfer_exec(int );
-char *lp_prexfer_exec(int );
-char *lp_refuse_options(int );
-char *lp_secrets_file(int );
-int lp_syslog_facility(int );
-char *lp_temp_dir(int );
-char *lp_uid(int );
-int lp_max_connections(int );
-int lp_max_verbosity(int );
-int lp_timeout(int );
-BOOL lp_ignore_errors(int );
-BOOL lp_ignore_nonreadable(int );
-BOOL lp_list(int );
-BOOL lp_read_only(int );
-BOOL lp_strict_modes(int );
-BOOL lp_transfer_logging(int );
-BOOL lp_use_chroot(int );
-BOOL lp_write_only(int );
+char *lp_auth_users(int module_id);
+char *lp_charset(int module_id);
+char *lp_comment(int module_id);
+char *lp_dont_compress(int module_id);
+char *lp_exclude(int module_id);
+char *lp_exclude_from(int module_id);
+char *lp_filter(int module_id);
+char *lp_gid(int module_id);
+char *lp_hosts_allow(int module_id);
+char *lp_hosts_deny(int module_id);
+char *lp_include(int module_id);
+char *lp_include_from(int module_id);
+char *lp_incoming_chmod(int module_id);
+char *lp_lock_file(int module_id);
+char *lp_log_file(int module_id);
+char *lp_log_format(int module_id);
+char *lp_name(int module_id);
+char *lp_outgoing_chmod(int module_id);
+char *lp_path(int module_id);
+char *lp_postxfer_exec(int module_id);
+char *lp_prexfer_exec(int module_id);
+char *lp_refuse_options(int module_id);
+char *lp_secrets_file(int module_id);
+char *lp_temp_dir(int module_id);
+char *lp_uid(int module_id);
+int lp_max_connections(int module_id);
+int lp_max_verbosity(int module_id);
+int lp_syslog_facility(int module_id);
+int lp_timeout(int module_id);
+BOOL lp_fake_super(int module_id);
+BOOL lp_ignore_errors(int module_id);
+BOOL lp_ignore_nonreadable(int module_id);
+BOOL lp_list(int module_id);
+BOOL lp_munge_symlinks(int module_id);
+BOOL lp_numeric_ids(int module_id);
+BOOL lp_read_only(int module_id);
+BOOL lp_strict_modes(int module_id);
+BOOL lp_transfer_logging(int module_id);
+BOOL lp_use_chroot(int module_id);
+BOOL lp_write_only(int module_id);
 BOOL lp_load(char *pszFname, int globals_only);
 int lp_numservices(void);
 int lp_number(char *name);
 void log_init(int restart);
 void logfile_close(void);
 void logfile_reopen(void);
-void rwrite(enum logcode code, char *buf, int len);
+void rwrite(enum logcode code, const char *buf, int len, int is_utf8);
 void rprintf(enum logcode code, const char *format, ...);
 void rsyserr(enum logcode code, int errcode, const char *format, ...);
 void rflush(enum logcode code);
 int log_format_has(const char *format, char esc);
 void log_item(enum logcode code, struct file_struct *file,
-	      struct stats *initial_stats, int iflags, char *hlink);
+	      struct stats *initial_stats, int iflags, const char *hlink);
 void maybe_log_item(struct file_struct *file, int iflags, int itemizing,
-		    char *buf);
-void log_delete(char *fname, int mode);
+		    const char *buf);
+void log_delete(const char *fname, int mode);
 void log_exit(int code, const char *file, int line);
 pid_t wait_process(pid_t pid, int *status_ptr, int flags);
 int child_main(int argc, char *argv[]);
 void start_server(int f_in, int f_out, int argc, char *argv[]);
 int client_run(int f_in, int f_out, pid_t pid, int argc, char *argv[]);
 RETSIGTYPE remember_children(UNUSED(int val));
 const char *get_panic_action(void);
 int main(int argc,char *argv[]);
 void match_sums(int f, struct sum_struct *s, struct map_struct *buf, OFF_T len);
 void match_report(void);
 void usage(enum logcode F);
 void option_error(void);
-int parse_arguments(int *argc, const char ***argv, int frommain);
-void server_options(char **args,int *argc);
+int parse_arguments(int *argc_p, const char ***argv_p, int frommain);
+void server_options(char **args, int *argc_p);
 char *check_for_hostspec(char *s, char **host_ptr, int *port_ptr);
 BOOL pm_process( char *FileName,
                  BOOL (*sfunc)(char *),
                  BOOL (*pfunc)(char *, char *) );
 pid_t piped_child(char **command, int *f_in, int *f_out);
 pid_t local_child(int argc, char **argv, int *f_in, int *f_out,
 		  int (*child_main)(int, char*[]));
+void set_current_file_index(struct file_struct *file, int ndx);
 void end_progress(OFF_T size);
 void show_progress(OFF_T ofs, OFF_T size);
-int recv_files(int f_in, struct file_list *flist, char *local_name);
-void setup_iconv();
+int get_tmpname(char *fnametmp, const char *fname);
+int open_tmpfile(char *fnametmp, const char *fname, struct file_struct *file);
+int recv_files(int f_in, char *local_name);
+void setup_iconv(void);
+int iconvbufs(iconv_t ic, xbuf *in, xbuf *out, int flags);
+int read_ndx_and_attrs(int f_in, int *iflag_ptr, uchar *type_ptr,
+		       char *buf, int *len_ptr);
 void free_sums(struct sum_struct *s);
-mode_t dest_mode(mode_t flist_mode, mode_t stat_mode, int exists);
-int set_file_attrs(char *fname, struct file_struct *file, STRUCT_STAT *st,
-		   int flags);
+mode_t dest_mode(mode_t flist_mode, mode_t stat_mode, int dflt_perms,
+		 int exists);
+int set_file_attrs(const char *fname, struct file_struct *file, stat_x *sxp,
+		   const char *fnamecmp, int flags);
 RETSIGTYPE sig_int(UNUSED(int val));
-void finish_transfer(char *fname, char *fnametmp, char *partialptr,
-		     struct file_struct *file, int ok_to_set_time,
-		     int overwriting_basis);
+int finish_transfer(const char *fname, const char *fnametmp,
+		    const char *fnamecmp, const char *partialptr,
+		    struct file_struct *file, int ok_to_set_time,
+		    int overwriting_basis);
+struct file_list *flist_for_ndx(int ndx);
 const char *who_am_i(void);
 void successful_send(int ndx);
-int read_item_attrs(int f_in, int f_out, int ndx, uchar *type_ptr,
-		    char *buf, int *len_ptr);
-void send_files(struct file_list *flist, int f_out, int f_in);
+void send_files(int f_in, int f_out);
 int try_bind_local(int s, int ai_family, int ai_socktype,
 		   const char *bind_addr);
 int open_socket_out(char *host, int port, const char *bind_addr,
 		    int af_hint);
 int open_socket_out_wrapped(char *host, int port, const char *bind_addr,
 			    int af_hint);
 int is_a_socket(int fd);
 void start_accept_loop(int port, int (*fn)(int, int));
 void set_socket_options(int fd, char *options);
-void become_daemon(void);
 int sock_exec(const char *prog);
 int do_unlink(const char *fname);
 int do_symlink(const char *fname1, const char *fname2);
 int do_link(const char *fname1, const char *fname2);
 int do_lchown(const char *path, uid_t owner, gid_t group);
-int do_mknod(char *pathname, mode_t mode, dev_t dev);
+int do_mknod(const char *pathname, mode_t mode, dev_t dev);
 int do_rmdir(const char *pathname);
 int do_open(const char *pathname, int flags, mode_t mode);
 int do_chmod(const char *path, mode_t mode);
 int do_rename(const char *fname1, const char *fname2);
 void trim_trailing_slashes(char *name);
 int do_mkdir(char *fname, mode_t mode);
 int do_mkstemp(char *template, mode_t perms);
 int do_stat(const char *fname, STRUCT_STAT *st);
 int do_lstat(const char *fname, STRUCT_STAT *st);
 int do_fstat(int fd, STRUCT_STAT *st);
 OFF_T do_lseek(int fd, OFF_T offset, int whence);
 char *d_name(struct dirent *di);
-void set_compression(char *fname);
+void set_compression(const char *fname);
 void send_token(int f, int32 token, struct map_struct *buf, OFF_T offset,
 		int32 n, int32 toklen);
 int32 recv_token(int f, char **data);
 void see_token(char *data, int32 toklen);
-void add_uid(uid_t uid);
-void add_gid(gid_t gid);
-void send_uid_list(int f);
-void recv_uid_list(int f, struct file_list *flist);
+uid_t match_uid(uid_t uid);
+gid_t match_gid(gid_t gid, uint16 *flags_ptr);
+const char *add_uid(uid_t uid);
+const char *add_gid(gid_t gid);
+void send_id_list(int f);
+uid_t recv_user_name(int f, uid_t uid);
+gid_t recv_group_name(int f, gid_t gid, uint16 *flags_ptr);
+void recv_id_list(int f, struct file_list *flist);
 void set_nonblocking(int fd);
 void set_blocking(int fd);
 int fd_pair(int fd[2]);
-void print_child_argv(char **cmd);
-NORETURN void out_of_memory(char *str);
-NORETURN void overflow_exit(char *str);
-int set_modtime(char *fname, time_t modtime, mode_t mode);
+void print_child_argv(const char *prefix, char **cmd);
+NORETURN void out_of_memory(const char *str);
+NORETURN void overflow_exit(const char *str);
+int set_modtime(const char *fname, time_t modtime, mode_t mode);
 int mkdir_defmode(char *fname);
 int create_directory_path(char *fname);
-int full_write(int desc, char *ptr, size_t len);
-int copy_file(const char *source, const char *dest, mode_t mode);
+int full_write(int desc, const char *ptr, size_t len);
+int copy_file(const char *source, const char *dest, int ofd,
+	      mode_t mode, int create_bak_dir);
 int robust_unlink(const char *fname);
-int robust_rename(char *from, char *to, char *partialptr,
+int robust_rename(const char *from, const char *to, const char *partialptr,
 		  int mode);
 pid_t do_fork(void);
 void kill_all(int sig);
-int name_to_uid(char *name, uid_t *uid);
-int name_to_gid(char *name, gid_t *gid);
+int name_to_uid(const char *name, uid_t *uid_p);
+int name_to_gid(const char *name, gid_t *gid_p);
 int lock_range(int fd, int offset, int len);
-void glob_expand(char *base1, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr);
+void glob_expand(char *s, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr);
+void glob_expand_module(char *base1, char *arg, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr);
 void strlower(char *s);
 size_t pathjoin(char *dest, size_t destsize, const char *p1, const char *p2);
 size_t stringjoin(char *dest, size_t destsize, ...);
 int count_dir_elements(const char *p);
-unsigned int clean_fname(char *name, BOOL collapse_dot_dot);
-char *sanitize_path(char *dest, const char *p, const char *rootdir, int depth,
-		    const char *symlink);
-int push_dir(char *dir, int set_path_only);
-int pop_dir(char *dir);
+unsigned int clean_fname(char *name, int flags);
+char *sanitize_path(char *dest, const char *p, const char *rootdir, int depth);
+int push_dir(const char *dir, int set_path_only);
+int pop_dir(const char *dir);
 char *full_fname(const char *fn);
 char *partial_dir_fname(const char *fname);
 int handle_partial_dir(const char *fname, int create);
 int unsafe_symlink(const char *dest, const char *src);
 char *human_num(int64 num);
 char *human_dnum(double dnum, int decimal_digits);
 char *timestring(time_t t);
 int msleep(int t);
 int cmp_time(time_t file1, time_t file2);
 int _Insure_trap_error(int a1, int a2, int a3, int a4, int a5, int a6);
-void *_new_array(unsigned int size, unsigned long num);
+void *_new_array(unsigned long num, unsigned int size, int use_calloc);
 void *_realloc_array(void *ptr, unsigned int size, unsigned long num);
 const char *find_filename_suffix(const char *fn, int fn_len, int *len_ptr);
 uint32 fuzzy_distance(const char *s1, int len1, const char *s2, int len2);
 struct bitbag *bitbag_create(int max_ndx);
 void bitbag_set_bit(struct bitbag *bb, int ndx);
 void bitbag_clear_bit(struct bitbag *bb, int ndx);
 int bitbag_check_bit(struct bitbag *bb, int ndx);
 int bitbag_next_bit(struct bitbag *bb, int after);
+void *expand_item_list(item_list *lp, size_t item_size,
+		       const char *desc, int incr);
+void free_xattr(stat_x *sxp);
+int get_xattr(const char *fname, stat_x *sxp);
+int send_xattr(stat_x *sxp, int f);
+int xattr_diff(struct file_struct *file, stat_x *sxp, int find_all);
+void send_xattr_request(const char *fname, struct file_struct *file, int f_out);
+int recv_xattr_request(struct file_struct *file, int f_in);
+void receive_xattr(struct file_struct *file, int f);
+void cache_xattr(struct file_struct *file, stat_x *sxp);
+int set_xattr(const char *fname, const struct file_struct *file,
+	      const char *fnamecmp, stat_x *sxp);
+char *get_xattr_acl(const char *fname, int is_access_acl, size_t *len_p);
+int set_xattr_acl(const char *fname, int is_access_acl, const char *buf, size_t buf_len);
+int del_def_xattr_acl(const char *fname);
+int get_stat_xattr(const char *fname, int fd, STRUCT_STAT *fst, STRUCT_STAT *xst);
+int set_stat_xattr(const char *fname, struct file_struct *file, mode_t new_mode);
+int x_stat(const char *fname, STRUCT_STAT *fst, STRUCT_STAT *xst);
+int x_lstat(const char *fname, STRUCT_STAT *fst, STRUCT_STAT *xst);
+int x_fstat(int fd, STRUCT_STAT *fst, STRUCT_STAT *xst);
 int sys_gettimeofday(struct timeval *tv);
