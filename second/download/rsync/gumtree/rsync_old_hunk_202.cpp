      }
      continue;
    }
    recv_generator(local_name?local_name:file->name,
		   flist,i,f);
  }
  write_int(f,-1);
  write_flush(f);
  if (verbose > 2)
    fprintf(FERROR,"generator wrote %d\n",write_total());
}


