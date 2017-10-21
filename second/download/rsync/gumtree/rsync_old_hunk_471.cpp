static int rx_run;

/* Receive a deflated token and inflate it */
static int
recv_deflated_token(int f, char **data)
{
    int n, r, flag;
    static int init_done;
    static int saved_flag;

    for (;;) {
	switch (recv_state) {
	case r_init:
	    if (!init_done) {
		rx_strm.next_out = NULL;
		rx_strm.zalloc = z_alloc;
		rx_strm.zfree = z_free;
		if (inflateInit2(&rx_strm, -15) != Z_OK) {
		    rprintf(FERROR, "inflate init failed\n");
		    exit_cleanup(1);
		}
		if ((cbuf = malloc(MAX_DATA_COUNT)) == NULL
		    || (dbuf = malloc(CHUNK_SIZE)) == NULL)
		    out_of_memory("recv_deflated_token");
		init_done = 1;
	    } else {
		inflateReset(&rx_strm);
	    }
	    recv_state = r_idle;
	    rx_token = 0;
	    break;
	    
	case r_idle:
	case r_inflated:
	    if (saved_flag) {
		flag = saved_flag & 0xff;
		saved_flag = 0;
	    } else
		flag = read_byte(f);
	    if ((flag & 0xC0) == DEFLATED_DATA) {
		n = ((flag & 0x3f) << 8) + read_byte(f);
		read_buf(f, cbuf, n);
		rx_strm.next_in = (Bytef *)cbuf;
		rx_strm.avail_in = n;
		recv_state = r_inflating;
		break;
	    }
	    if (recv_state == r_inflated) {
		/* check previous inflated stuff ended correctly */
		rx_strm.avail_in = 0;
		rx_strm.next_out = (Bytef *)dbuf;
		rx_strm.avail_out = CHUNK_SIZE;
		r = inflate(&rx_strm, Z_PACKET_FLUSH);
		n = CHUNK_SIZE - rx_strm.avail_out;
		if (r != Z_OK) {
		    rprintf(FERROR, "inflate flush returned %d (%d bytes)\n",
			    r, n);
		    exit_cleanup(1);
		}
		if (n != 0) {
		    /* have to return some more data and
		       save the flag for later. */
		    saved_flag = flag + 0x10000;
		    if (rx_strm.avail_out != 0)
			recv_state = r_idle;
		    *data = dbuf;
		    return n;
		}
		recv_state = r_idle;
	    }
	    if (flag == END_FLAG) {
		/* that's all folks */
		recv_state = r_init;
		return 0;
	    }

	    /* here we have a token of some kind */
	    if (flag & TOKEN_REL) {
		rx_token += flag & 0x3f;
		flag >>= 6;
	    } else
		rx_token = read_int(f);
	    if (flag & 1) {
		rx_run = read_byte(f);
		rx_run += read_byte(f) << 8;
		recv_state = r_running;
	    }
	    return -1 - rx_token;

	case r_inflating:
	    rx_strm.next_out = (Bytef *)dbuf;
	    rx_strm.avail_out = CHUNK_SIZE;
	    r = inflate(&rx_strm, Z_NO_FLUSH);
	    n = CHUNK_SIZE - rx_strm.avail_out;
	    if (r != Z_OK) {
		rprintf(FERROR, "inflate returned %d (%d bytes)\n", r, n);
		exit_cleanup(1);
	    }
	    if (rx_strm.avail_in == 0)
		recv_state = r_inflated;
	    if (n != 0) {
		*data = dbuf;
		return n;
	    }
	    break;

	case r_running:
	    ++rx_token;
	    if (--rx_run == 0)
		recv_state = r_idle;
	    return -1 - rx_token;
	}
    }
}

/*
 * put the data corresponding to a token that we've just returned
 * from recv_deflated_token into the decompressor's history buffer.
 */
void
see_deflate_token(char *buf, int len)
{
    int r;

    rx_strm.next_in = (Bytef *)buf;
    rx_strm.avail_in = len;
    r = inflateIncomp(&rx_strm);
    if (r != Z_OK) {
	rprintf(FERROR, "inflateIncomp returned %d\n", r);
	exit_cleanup(1);
    }
}

/*
 * transmit a verbatim buffer of length n followed by a token 
 * If token == -1 then we have reached EOF 
 * If n == 0 then don't send a buffer
 */
void send_token(int f,int token,struct map_struct *buf,int offset,
		int n,int toklen)
{
  if (!do_compression) {
    simple_send_token(f,token,buf,offset,n);
  } else {
    send_deflated_token(f, token, buf, offset, n, toklen);
  }
}


/*
 * receive a token or buffer from the other end. If the reurn value is >0 then
 * it is a data buffer of that length, and *data will point at the data.
 * if the return value is -i then it represents token i-1
 * if the return value is 0 then the end has been reached
 */
int recv_token(int f,char **data)
{
  int tok;

  if (!do_compression) {
    tok = simple_recv_token(f,data);
  } else {
    tok = recv_deflated_token(f, data);
  }
  return tok;
}

/*
 * look at the data corresponding to a token, if necessary
 */
void see_token(char *data, int toklen)
{
    if (do_compression)
	see_deflate_token(data, toklen);
}
