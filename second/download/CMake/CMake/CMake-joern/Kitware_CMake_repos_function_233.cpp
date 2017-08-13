static int
mtree_entry_exchange_same_entry(struct archive_write *a, struct mtree_entry *np,
    struct mtree_entry *file)
{

	if ((np->mode & AE_IFMT) != (file->mode & AE_IFMT)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Found duplicate entries `%s' and its file type is "
		    "different",
		    np->pathname.s);
		return (ARCHIVE_FAILED);
	}

	/* Update the existent mtree entry's attributes by the new one's. */
	archive_string_empty(&np->symlink);
	archive_string_concat(&np->symlink, &file->symlink);
	archive_string_empty(&np->uname);
	archive_string_concat(&np->uname, &file->uname);
	archive_string_empty(&np->gname);
	archive_string_concat(&np->gname, &file->gname);
	archive_string_empty(&np->fflags_text);
	archive_string_concat(&np->fflags_text, &file->fflags_text);
	np->nlink = file->nlink;
	np->filetype = file->filetype;
	np->mode = file->mode;
	np->size = file->size;
	np->uid = file->uid;
	np->gid = file->gid;
	np->fflags_set = file->fflags_set;
	np->fflags_clear = file->fflags_clear;
	np->mtime = file->mtime;
	np->mtime_nsec = file->mtime_nsec;
	np->rdevmajor = file->rdevmajor;
	np->rdevminor = file->rdevminor;
	np->devmajor = file->devmajor;
	np->devminor = file->devminor;
	np->ino = file->ino;

	return (ARCHIVE_WARN);
}