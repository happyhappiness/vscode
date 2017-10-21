		return -1;
	}

	return 0;
}

/*
  send a sums struct down a fd
  */
static void send_sums(struct sum_struct *s,int f_out)
{
	int i;

  /* tell the other guy how many we are going to be doing and how many
     bytes there are in the last chunk */
	write_int(f_out,s?s->count:0);
	write_int(f_out,s?s->n:block_size);
	write_int(f_out,s?s->remainder:0);
	if (s)
		for (i=0;i<s->count;i++) {
			write_int(f_out,s->sums[i].sum1);
			write_buf(f_out,s->sums[i].sum2,csum_length);
		}
}


/*
  generate a stream of signatures/checksums that describe a buffer

  generate approximately one checksum every n bytes
  */
static struct sum_struct *generate_sums(struct map_struct *buf,OFF_T len,int n)
{
	int i;
	struct sum_struct *s;
	int count;
	int block_len = n;
	int remainder = (len%block_len);
	OFF_T offset = 0;

	count = (len+(block_len-1))/block_len;

	s = (struct sum_struct *)malloc(sizeof(*s));
	if (!s) out_of_memory("generate_sums");

	s->count = count;
	s->remainder = remainder;
	s->n = n;
	s->flength = len;

	if (count==0) {
		s->sums = NULL;
		return s;
	}

	if (verbose > 3)
		rprintf(FINFO,"count=%d rem=%d n=%d flength=%d\n",
			s->count,s->remainder,s->n,(int)s->flength);

	s->sums = (struct sum_buf *)malloc(sizeof(s->sums[0])*s->count);
	if (!s->sums) out_of_memory("generate_sums");
  
	for (i=0;i<count;i++) {
		int n1 = MIN(len,n);
		char *map = map_ptr(buf,offset,n1);

		s->sums[i].sum1 = get_checksum1(map,n1);
		get_checksum2(map,n1,s->sums[i].sum2);

		s->sums[i].offset = offset;
		s->sums[i].len = n1;
		s->sums[i].i = i;

		if (verbose > 3)
			rprintf(FINFO,"chunk[%d] offset=%d len=%d sum1=%08x\n",
				i,(int)s->sums[i].offset,s->sums[i].len,s->sums[i].sum1);

		len -= n1;
		offset += n1;
	}

	return s;
}


/*
  receive the checksums for a buffer
  */
static struct sum_struct *receive_sums(int f)
{
	struct sum_struct *s;
	int i;
	OFF_T offset = 0;

	s = (struct sum_struct *)malloc(sizeof(*s));
	if (!s) out_of_memory("receive_sums");

	s->count = read_int(f);
	s->n = read_int(f);
	s->remainder = read_int(f);  
	s->sums = NULL;

	if (verbose > 3)
		rprintf(FINFO,"count=%d n=%d rem=%d\n",
			s->count,s->n,s->remainder);

	if (s->count == 0) 
		return(s);

	s->sums = (struct sum_buf *)malloc(sizeof(s->sums[0])*s->count);
	if (!s->sums) out_of_memory("receive_sums");

	for (i=0;i<s->count;i++) {
		s->sums[i].sum1 = read_int(f);
		read_buf(f,s->sums[i].sum2,csum_length);

		s->sums[i].offset = offset;
		s->sums[i].i = i;

		if (i == s->count-1 && s->remainder != 0) {
			s->sums[i].len = s->remainder;
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
	extern int am_daemon;

	if (dry_run) return 0;
