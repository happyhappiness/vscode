    }
  return 1;
}

/*
 * compress stdin to stdout
 *
 * Algorithm:  use open addressing double hashing (no chaining) on the
 * prefix code / next character combination.  We do a variant of Knuth's
 * algorithm D (vol. 3, sec. 6.4) along with G. Knott's relatively-prime
 * secondary probe.  Here, the modular division first probe is gives way
 * to a faster exclusive-or manipulation.  Also do block compression with
 * an adaptive reset, whereby the code table is cleared when the compression
 * ratio decreases, but after the table fills.  The variable-length output
 * codes are re-sized at this point, and a special CLEAR code is generated
 * for the decompressor.  Late addition:  construct the table according to
 * file size for noticeable speed improvement on small files.  Please direct
 * questions about this implementation to ames!jaw.
 */

int cmcompress_compress_start(struct cmcompress_stream* cdata)
{
#ifndef COMPATIBLE
  if (cdata->nomagic == 0)
    {
    char headLast = (char)(cdata->maxbits | cdata->block_compress);
    cdata->output_stream(cdata, (const char*)magic_header, 2);
    cdata->output_stream(cdata, &headLast, 1);
    if(ferror(stdout))
      {
      printf("Error...\n");
      }
    }
#endif /* COMPATIBLE */

  cdata->offset = 0;
  cdata->bytes_out = 3;    /* includes 3-byte header mojo */
  cdata->out_count = 0;
  cdata->clear_flg = 0;
  cdata->ratio = 0;
  cdata->in_count = 1;
  cdata->checkpoint = CHECK_GAP;
  cdata->maxcode = MAXCODE(cdata->n_bits = INIT_BITS);
  cdata->free_ent = ((cdata->block_compress) ? FIRST : 256 );

  cdata->first_pass = 1;

  cdata->hshift = 0;
  for ( cdata->fcode = (long) cdata->hsize;  cdata->fcode < 65536L; cdata->fcode *= 2L )
    {
    cdata->hshift++;
    }
  cdata->hshift = 8 - cdata->hshift;    /* set hash code range bound */

  cdata->hsize_reg = cdata->hsize;
  cl_hash(cdata, (count_int) cdata->hsize_reg);    /* clear hash table */

  return 1;
}

static int cl_block (struct cmcompress_stream* cdata)    /* table clear for block compress */
{
  register long int rat;

  cdata->checkpoint = cdata->in_count + CHECK_GAP;
#ifdef DEBUG
  if ( cdata->debug )
    {
    fprintf ( stderr, "count: %ld, ratio: ", cdata->in_count );
    prratio ( stderr, cdata->in_count, cdata->bytes_out );
    fprintf ( stderr, "\n");
    }
#endif /* DEBUG */

  if(cdata->in_count > 0x007fffff)
    {  /* shift will overflow */
    rat = cdata->bytes_out >> 8;
    if(rat == 0)
      {    /* Don't divide by zero */
      rat = 0x7fffffff;
      }
    else
      {
      rat = cdata->in_count / rat;
      }
    }
  else
    {
    rat = (cdata->in_count << 8) / cdata->bytes_out;  /* 8 fractional bits */
    }
  if ( rat > cdata->ratio )
    {
    cdata->ratio = rat;
    }
  else
    {
    cdata->ratio = 0;
#ifdef DEBUG
    if(cdata->verbose)
      {
      dump_tab();  /* dump string table */
      }
#endif
    cl_hash (cdata, (count_int) cdata->hsize );
    cdata->free_ent = FIRST;
    cdata->clear_flg = 1;
    if ( !output (cdata, (code_int) CLEAR ) )
      {
      return 0;
      }
#ifdef DEBUG
    if(cdata->debug)
      {
      fprintf ( stderr, "clear\n" );
      }
#endif /* DEBUG */
    }
  return 1;
}


int cmcompress_compress(struct cmcompress_stream* cdata, void* buff, size_t n)
{
  register code_int i;
  register int c;
  register int disp;

  unsigned char* input_buffer = (unsigned char*)buff;

  size_t cc;

  /*printf("cmcompress_compress(%p, %p, %d)\n", cdata, buff, n);*/

  if ( cdata->first_pass )
    {
    cdata->ent = input_buffer[0];
    ++ input_buffer;
    -- n;
    cdata->first_pass = 0;
    }

  for ( cc = 0; cc < n; ++ cc )
    {
    c = input_buffer[cc];
    cdata->in_count++;
    cdata->fcode = (long) (((long) c << cdata->maxbits) + cdata->ent);
    i = ((c << cdata->hshift) ^ cdata->ent);  /* xor hashing */

    if ( htabof (i) == cdata->fcode )
      {
      cdata->ent = codetabof (i);
      continue;
      }
    else if ( (long)htabof (i) < 0 )  /* empty slot */
      {
      goto nomatch;
      }
    disp = cdata->hsize_reg - i;    /* secondary hash (after G. Knott) */
    if ( i == 0 )
      {
      disp = 1;
      }
probe:
    if ( (i -= disp) < 0 )
      {
      i += cdata->hsize_reg;
      }

    if ( htabof (i) == cdata->fcode )
      {
      cdata->ent = codetabof (i);
      continue;
      }
    if ( (long)htabof (i) > 0 )
      {
      goto probe;
      }
nomatch:
    if ( !output(cdata, (code_int) cdata->ent ) )
      {
      return 0;
      }
    cdata->out_count++;
    cdata->ent = c;
    if (
#ifdef SIGNED_COMPARE_SLOW
      (unsigned) cdata->free_ent < (unsigned) cdata->maxmaxcode
#else
      cdata->free_ent < cdata->maxmaxcode
#endif
    )
      {
      codetabof (i) = (unsigned short)(cdata->free_ent++);  /* code -> hashtable */
      htabof (i) = cdata->fcode;
      }
    else if ( (count_int)cdata->in_count >= cdata->checkpoint && cdata->block_compress )
      {
      if ( !cl_block (cdata) )
        {
        return 0;
        }
      }
    }

  return 1;
}

int cmcompress_compress_finalize(struct cmcompress_stream* cdata)
{
  /*
   * Put out the final code.
   */
  if ( !output(cdata, (code_int)cdata->ent ) )
    {
    return 0;
    }
  cdata->out_count++;
  if ( !output(cdata, (code_int)-1 ) )
    {
    return 0;
    }

  if(cdata->bytes_out > cdata->in_count)  /* exit(2) if no savings */
    {
    return 0;
    }
  return 1;
}


#if defined(DEBUG)
static void prratio(FILE *stream, long int num, long int den)
{
  register int q;      /* Doesn't need to be long */

  if(num > 214748L)
    {    /* 2147483647/10000 */
    q = num / (den / 10000L);
    }
  else
    {
    q = 10000L * num / den;    /* Long calculations, though */
    }
  if (q < 0)
    {
    putc('-', stream);
    q = -q;
    }
  fprintf(stream, "%d.%02d%%", q / 100, q % 100);
}
#endif
