extern int csum_length;
extern int read_batch;
extern int write_batch;
extern int batch_gen_fd;
extern int protocol_version;
extern int relative_paths;
extern int preserve_hard_links;
extern int preserve_perms;
extern int basis_dir_cnt;
extern int make_backups;
extern int cleanup_got_literal;
extern int remove_sent_files;
extern int append_mode;
extern int sparse_files;
extern int keep_partial;
extern int checksum_seed;
extern int inplace;
extern int delay_updates;
extern struct stats stats;
extern char *log_format;
extern char *tmpdir;
extern char *partial_dir;
extern char *basis_dir[];
extern struct file_list *the_file_list;
extern struct filter_list_struct server_filter_list;

static struct bitbag *delayed_bits = NULL;
static int phase = 0;


/*
 * get_tmpname() - create a tmp filename for a given filename
 *
 *   If a tmpdir is defined, use that as the directory to
 *   put it in.  Otherwise, the tmp filename is in the same
