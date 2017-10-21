    } else {
      s->sums[i].len = s->n;
    }
    offset += s->sums[i].len;

    if (verbose > 3)
      rprintf(FINFO,"chunk[%d] len=%d offset=%d sum1=%08x\n",
	      i,s->sums[i].len,(int)s->sums[i].offset,s->sums[i].sum1);
  }

  s->flength = offset;

  return s;
}


static int set_perms(char *fname,struct file_struct *file,STRUCT_STAT *st,
		     int report)
{
  int updated = 0;
  STRUCT_STAT st2;

  if (dry_run) return 0;

  if (!st) {
    if (link_stat(fname,&st2) != 0) {
      rprintf(FERROR,"stat %s : %s\n",fname,strerror(errno));
      return 0;
    }
    st = &st2;
  }

  if (preserve_times && !S_ISLNK(st->st_mode) &&
      st->st_mtime != file->modtime) {
    updated = 1;
    if (set_modtime(fname,file->modtime) != 0) {
      rprintf(FERROR,"failed to set times on %s : %s\n",
	      fname,strerror(errno));
      return 0;
    }
  }

#ifdef HAVE_CHMOD
  if (preserve_perms && !S_ISLNK(st->st_mode) &&
      st->st_mode != file->mode) {
    updated = 1;
    if (do_chmod(fname,file->mode) != 0) {
      rprintf(FERROR,"failed to set permissions on %s : %s\n",
	      fname,strerror(errno));
      return 0;
    }
  }
#endif

