
#define HFS_BLOCKS(s)	((s) >> 12)

static int	check_symlinks(struct archive_write_disk *);
static int	create_filesystem_object(struct archive_write_disk *);
static struct fixup_entry *current_fixup(struct archive_write_disk *, const char *pathname);
#if defined(HAVE_FCHDIR) && defined(PATH_MAX)
static void	edit_deep_directories(struct archive_write_disk *ad);
#endif
static int	cleanup_pathname(struct archive_write_disk *);
static int	create_dir(struct archive_write_disk *, char *);
static int	create_parent_dir(struct archive_write_disk *, char *);
