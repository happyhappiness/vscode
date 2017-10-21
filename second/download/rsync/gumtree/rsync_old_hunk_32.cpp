  s->flength = offset;

  return s;
}


static void set_perms(char *fname,struct file_struct *file)
{
  if (dry_run) return;

#ifdef HAVE_UTIME
  if (preserve_times) {
    struct utimbuf tbuf;  
    tbuf.actime = time(NULL);
    tbuf.modtime = file->modtime;
    if (utime(fname,&tbuf) != 0)
      fprintf(stderr,"failed to set times on %s : %s\n",
	      fname,strerror(errno));
  }
#endif

#ifdef HAVE_CHMOD
  if (preserve_perms) {
    if (chmod(fname,file->mode) != 0)
      fprintf(stderr,"failed to set permissions on %s : %s\n",
	      fname,strerror(errno));
  }
#endif

#ifdef HAVE_CHOWN
  if (preserve_uid || preserve_gid) {
    if (chown(fname,
	      preserve_uid?file->uid:-1,
	      preserve_gid?file->gid:-1) != 0) {
      fprintf(stderr,"chown %s : %s\n",fname,strerror(errno));
    }
  }
#endif
}


void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
  int fd;
