        if (csum_length == SUM_LENGTH)
	  fprintf(FERROR,"ERROR: file corruption in %s\n",fname);
	write_int(f_gen,i);
      }
    }

  /* now we need to fix any directory permissions that were 
     modified during the transfer */
  if (!am_root) {
    for (i = 0; i < flist->count; i++) {
      struct file_struct *file = &flist->files[i];
      if (!file->name || !S_ISDIR(file->mode)) continue;
      recv_generator(file->name,flist,i,-1);
    }
  }
  

  if (verbose > 2)
    fprintf(FERROR,"recv_files finished\n");
  
  return 0;
}
