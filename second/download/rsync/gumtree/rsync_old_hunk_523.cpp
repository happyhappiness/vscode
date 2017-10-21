			rprintf(FINFO,"%s is uptodate\n",fname);
	}
	return updated;
}


/* choose whether to skip a particular file */
static int skip_file(char *fname,
		     struct file_struct *file, STRUCT_STAT *st)
{
	if (st->st_size != file->length) {
		return 0;
	}
	
	/* if always checksum is set then we use the checksum instead 
	   of the file time to determine whether to sync */
	if (always_checksum && S_ISREG(st->st_mode)) {
		char sum[MD4_SUM_LENGTH];
		file_checksum(fname,sum,st->st_size);
		return (memcmp(sum,file->sum,csum_length) == 0);
	}

	if (ignore_times) {
		return 0;
	}

	return (st->st_mtime == file->modtime);
}


/* use a larger block size for really big files */
static int adapt_block_size(struct file_struct *file, int bsize)
{
	int ret;

	if (bsize != BLOCK_SIZE) return bsize;

	ret = file->length / (10000); /* rough heuristic */
	ret = ret & ~15; /* multiple of 16 */
	if (ret < bsize) ret = bsize;
	if (ret > CHUNK_SIZE/2) ret = CHUNK_SIZE/2;
	return ret;
}

static void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
	int fd;
	STRUCT_STAT st;
	struct map_struct *buf;
	struct sum_struct *s;
	int statret;
	struct file_struct *file = flist->files[i];

	if (verbose > 2)
		rprintf(FINFO,"recv_generator(%s,%d)\n",fname,i);

	statret = link_stat(fname,&st);

	if (S_ISDIR(file->mode)) {
		if (dry_run) return;
		if (statret == 0 && !S_ISDIR(st.st_mode)) {
			if (do_unlink(fname) != 0) {
				rprintf(FERROR,"unlink %s : %s\n",fname,strerror(errno));
				return;
			}
			statret = -1;
		}
		if (statret != 0 && do_mkdir(fname,file->mode) != 0 && errno != EEXIST) {
			if (!(relative_paths && errno==ENOENT && 
			      create_directory_path(fname)==0 && 
			      do_mkdir(fname,file->mode)==0)) {
				rprintf(FERROR,"mkdir %s : %s (2)\n",
					fname,strerror(errno));
			}
		}
		if (set_perms(fname,file,NULL,0) && verbose) 
			rprintf(FINFO,"%s/\n",fname);
		return;
	}

	if (preserve_links && S_ISLNK(file->mode)) {
#if SUPPORT_LINKS
		char lnk[MAXPATHLEN];
		int l;
		extern int safe_symlinks;

		if (safe_symlinks && unsafe_symlink(file->link, fname)) {
			if (verbose) {
				rprintf(FINFO,"ignoring unsafe symlink %s -> %s\n",
					fname,file->link);
			}
			return;
		}
		if (statret == 0) {
			l = readlink(fname,lnk,MAXPATHLEN-1);
			if (l > 0) {
				lnk[l] = 0;
				if (strcmp(lnk,file->link) == 0) {
					set_perms(fname,file,&st,1);
					return;
				}
			}
		}
		delete_file(fname);
		if (do_symlink(file->link,fname) != 0) {
			rprintf(FERROR,"link %s -> %s : %s\n",
				fname,file->link,strerror(errno));
		} else {
			set_perms(fname,file,NULL,0);
			if (verbose) {
				rprintf(FINFO,"%s -> %s\n",
					fname,file->link);
			}
		}
#endif
		return;
	}

#ifdef HAVE_MKNOD
	if (am_root && preserve_devices && IS_DEVICE(file->mode)) {
		if (statret != 0 || 
		    st.st_mode != file->mode ||
		    st.st_rdev != file->rdev) {	
			delete_file(fname);
			if (verbose > 2)
				rprintf(FINFO,"mknod(%s,0%o,0x%x)\n",
					fname,(int)file->mode,(int)file->rdev);
			if (do_mknod(fname,file->mode,file->rdev) != 0) {
				rprintf(FERROR,"mknod %s : %s\n",fname,strerror(errno));
			} else {
				set_perms(fname,file,NULL,0);
				if (verbose)
					rprintf(FINFO,"%s\n",fname);
			}
		} else {
			set_perms(fname,file,&st,1);
		}
		return;
	}
#endif

	if (preserve_hard_links && check_hard_link(file)) {
		if (verbose > 1)
			rprintf(FINFO,"%s is a hard link\n",f_name(file));
		return;
	}

	if (!S_ISREG(file->mode)) {
		rprintf(FINFO,"skipping non-regular file %s\n",fname);
		return;
	}

	if (statret == -1) {
		if (errno == ENOENT) {
			write_int(f_out,i);
			if (!dry_run) send_sums(NULL,f_out);
		} else {
			if (verbose > 1)
				rprintf(FERROR,"recv_generator failed to open %s\n",fname);
		}
		return;
	}

	if (!S_ISREG(st.st_mode)) {
		if (delete_file(fname) != 0) {
			return;
		}

		/* now pretend the file didn't exist */
		write_int(f_out,i);
		if (!dry_run) send_sums(NULL,f_out);    
		return;
	}

	if (update_only && st.st_mtime > file->modtime) {
		if (verbose > 1)
			rprintf(FINFO,"%s is newer\n",fname);
		return;
	}

	if (skip_file(fname, file, &st)) {
		set_perms(fname,file,&st,1);
		return;
	}

	if (dry_run) {
		write_int(f_out,i);
		return;
	}

	if (whole_file) {
		write_int(f_out,i);
		send_sums(NULL,f_out);    
		return;
	}

	/* open the file */  
	fd = open(fname,O_RDONLY);

	if (fd == -1) {
		rprintf(FERROR,"failed to open %s : %s\n",fname,strerror(errno));
		rprintf(FERROR,"skipping %s\n",fname);
		return;
	}

	if (st.st_size > 0) {
		buf = map_file(fd,st.st_size);
	} else {
		buf = NULL;
	}

	if (verbose > 3)
		rprintf(FINFO,"gen mapped %s of size %d\n",fname,(int)st.st_size);

	s = generate_sums(buf,st.st_size,adapt_block_size(file, block_size));

	if (verbose > 2)
		rprintf(FINFO,"sending sums for %d\n",i);

	write_int(f_out,i);
	send_sums(s,f_out);

	close(fd);
	if (buf) unmap_file(buf);

	free_sums(s);
}



static int receive_data(int f_in,struct map_struct *buf,int fd,char *fname,
			OFF_T total_size)
{
	int i,n,remainder,len,count;
	OFF_T offset = 0;
	OFF_T offset2;
	char *data;
	static char file_sum1[MD4_SUM_LENGTH];
	static char file_sum2[MD4_SUM_LENGTH];
	char *map=NULL;
	
	count = read_int(f_in);
	n = read_int(f_in);
	remainder = read_int(f_in);
	
	sum_init();
	
	for (i=recv_token(f_in,&data); i != 0; i=recv_token(f_in,&data)) {

		show_progress(offset, total_size);

		if (i > 0) {
			if (verbose > 3) {
				rprintf(FINFO,"data recv %d at %d\n",
					i,(int)offset);
			}

			stats.literal_data += i;
			cleanup_got_literal = 1;
      
			sum_update(data,i);

			if (fd != -1 && write_file(fd,data,i) != i) {
				rprintf(FERROR,"write failed on %s : %s\n",fname,strerror(errno));
				exit_cleanup(1);
			}
			offset += i;
			continue;
		} 

		i = -(i+1);
		offset2 = i*n;
		len = n;
		if (i == count-1 && remainder != 0)
			len = remainder;
		
		stats.matched_data += len;
		
		if (verbose > 3)
			rprintf(FINFO,"chunk[%d] of size %d at %d offset=%d\n",
				i,len,(int)offset2,(int)offset);
		
		map = map_ptr(buf,offset2,len);
		
		see_token(map, len);
		sum_update(map,len);
		
		if (fd != -1 && write_file(fd,map,len) != len) {
			rprintf(FERROR,"write failed on %s : %s\n",
				fname,strerror(errno));
			exit_cleanup(1);
		}
		offset += len;
	}

	end_progress();

	if (fd != -1 && offset > 0 && sparse_end(fd) != 0) {
		rprintf(FERROR,"write failed on %s : %s\n",
			fname,strerror(errno));
		exit_cleanup(1);
	}

	sum_end(file_sum1);

	if (remote_version >= 14) {
		read_buf(f_in,file_sum2,MD4_SUM_LENGTH);
		if (verbose > 2) {
			rprintf(FINFO,"got file_sum\n");
		}
		if (fd != -1 && 
		    memcmp(file_sum1,file_sum2,MD4_SUM_LENGTH) != 0) {
			return 0;
		}
	}
	return 1;
}


static void delete_one(struct file_struct *f)
{
	if (!S_ISDIR(f->mode)) {
		if (do_unlink(f_name(f)) != 0) {
			rprintf(FERROR,"unlink %s : %s\n",f_name(f),strerror(errno));
		} else if (verbose) {
			rprintf(FINFO,"deleting %s\n",f_name(f));
		}
	} else {    
		if (do_rmdir(f_name(f)) != 0) {
			if (errno != ENOTEMPTY && errno != EEXIST)
				rprintf(FERROR,"rmdir %s : %s\n",f_name(f),strerror(errno));
		} else if (verbose) {
			rprintf(FINFO,"deleting directory %s\n",f_name(f));      
		}
	}
}



static struct delete_list {
	dev_t dev;
	INO_T inode;
} *delete_list;
static int dlist_len, dlist_alloc_len;

static void add_delete_entry(struct file_struct *file)
{
	if (dlist_len == dlist_alloc_len) {
		dlist_alloc_len += 1024;
		delete_list = (struct delete_list *)Realloc(delete_list, sizeof(delete_list[0])*dlist_alloc_len);
		if (!delete_list) out_of_memory("add_delete_entry");
	}

	delete_list[dlist_len].dev = file->dev;
	delete_list[dlist_len].inode = file->inode;
	dlist_len++;

	if (verbose > 3)
		rprintf(FINFO,"added %s to delete list\n", f_name(file));
}

/* yuck! This function wouldn't have been necessary if I had the sorting
   algorithm right. Unfortunately fixing the sorting algorithm would introduce
   a backward incompatibility as file list indexes are sent over the link.
*/
static int delete_already_done(struct file_list *flist,int j)
{
	int i;
	STRUCT_STAT st;

	if (link_stat(f_name(flist->files[j]), &st)) return 1;

	for (i=0;i<dlist_len;i++) {
		if (st.st_ino == delete_list[i].inode &&
		    st.st_dev == delete_list[i].dev)
			return 1;
	}

	return 0;
}


/* this deletes any files on the receiving side that are not present
   on the sending side. For version 1.6.4 I have changed the behaviour
   to match more closely what most people seem to expect of this option */
static void delete_files(struct file_list *flist)
{
	struct file_list *local_file_list;
	int i, j;
	char *name;

	if (cvs_exclude)
		add_cvs_excludes();

	if (io_error) {
		rprintf(FINFO,"IO error encountered - skipping file deletion\n");
		return;
	}

	for (j=0;j<flist->count;j++) {
		if (!S_ISDIR(flist->files[j]->mode) || 
		    !(flist->files[j]->flags & FLAG_DELETE)) continue;

		if (remote_version < 19 &&
		    delete_already_done(flist, j)) continue;

		name = strdup(f_name(flist->files[j]));

		if (!(local_file_list = send_file_list(-1,1,&name))) {
			free(name);
			continue;
		}

		if (verbose > 1)
			rprintf(FINFO,"deleting in %s\n", name);

		for (i=local_file_list->count-1;i>=0;i--) {
			if (!local_file_list->files[i]->basename) continue;
			if (remote_version < 19 &&
			    S_ISDIR(local_file_list->files[i]->mode))
				add_delete_entry(local_file_list->files[i]);
			if (-1 == flist_find(flist,local_file_list->files[i])) {
				delete_one(local_file_list->files[i]);
			}    
		}
		flist_free(local_file_list);
		free(name);
	}
}

void sig_int(void)
{
	exit_cleanup(1);
}




static int get_tmpname(char *fnametmp, char *fname)
{
	char *f;

	/* open tmp file */
	if (tmpdir) {
		f = strrchr(fname,'/');
		if (f == NULL) 
			f = fname;
		else 
			f++;
		if (strlen(tmpdir)+strlen(f)+10 > MAXPATHLEN) {
			rprintf(FERROR,"filename too long\n");
			return 0;
		}
		slprintf(fnametmp,MAXPATHLEN-1, "%s/.%s.XXXXXX",tmpdir,f);
		return 1;
	} 

	f = strrchr(fname,'/');

	if (strlen(fname)+9 > MAXPATHLEN) {
		rprintf(FERROR,"filename too long\n");
		return 0;
	}

	if (f) {
		*f = 0;
		slprintf(fnametmp,MAXPATHLEN-1,"%s/.%s.XXXXXX",
			 fname,f+1);
		*f = '/';
	} else {
		slprintf(fnametmp,MAXPATHLEN-1,".%s.XXXXXX",fname);
	}

	return 1;
}

/* finish off a file transfer, renaming the file and setting the permissions
   and ownership */
static void finish_transfer(char *fname, char *fnametmp, struct file_struct *file)
{
	if (make_backups) {
		char fnamebak[MAXPATHLEN];
		if (strlen(fname) + strlen(backup_suffix) > (MAXPATHLEN-1)) {
			rprintf(FERROR,"backup filename too long\n");
			return;
