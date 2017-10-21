
extern int remote_version;
extern int verbose;

void setup_protocol(int f_out,int f_in)
{
  if (am_server) {
    remote_version = read_int(f_in);
    write_int(f_out,PROTOCOL_VERSION);
    write_flush(f_out);
  } else {
    write_int(f_out,PROTOCOL_VERSION);
    write_flush(f_out);
    remote_version = read_int(f_in);
  }

  if (remote_version < MIN_PROTOCOL_VERSION ||
      remote_version > MAX_PROTOCOL_VERSION) {
    fprintf(FERROR,"protocol version mismatch - is your shell clean?\n");
    exit_cleanup(1);
  }	

  if (verbose > 2)
	  fprintf(FINFO, "local_version=%d remote_version=%d\n",
		  PROTOCOL_VERSION, remote_version);

  if (remote_version >= 12) {
    if (am_server) {
      checksum_seed = time(NULL);
      write_int(f_out,checksum_seed);
    } else {
      checksum_seed = read_int(f_in);
    }
  }

  checksum_init();
}

