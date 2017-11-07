int
md5_stream (FILE *stream, void *resblock)
{
  struct md5_ctx ctx;
  char buffer[BLOCKSIZE + 72];
  size_t sum;

  /* Initialize the computation context.  */
  md5_init_ctx (&ctx);

  /* Iterate over full file contents.  */
  while (1)
    {
      /* We read the file in blocks of BLOCKSIZE bytes.  One call of the
         computation function processes the whole buffer so that with the
         next round of the loop another block can be read.  */
      size_t n;
      sum = 0;

      /* Read block.  Take care for partial reads.  */
      while (1)
	{
	  n = fread (buffer + sum, 1, BLOCKSIZE - sum, stream);

	  sum += n;

	  if (sum == BLOCKSIZE)
	    break;

	  if (n == 0)
	    {
	      /* Check for the error flag IFF N == 0, so that we don't
	         exit the loop after a partial read due to e.g., EAGAIN
	         or EWOULDBLOCK.  */
	      if (ferror (stream))
		return 1;
	      goto process_partial_block;
	    }

	  /* We've read at least one byte, so ignore errors.  But always
	     check for EOF, since feof may be true even though N > 0.
	     Otherwise, we could end up calling fread after EOF.  */
	  if (feof (stream))
	    goto process_partial_block;
	}

      /* Process buffer with BLOCKSIZE bytes.  Note that
         BLOCKSIZE % 64 == 0
       */
      md5_process_block (buffer, BLOCKSIZE, &ctx);
    }

process_partial_block:

  /* Process any remaining bytes.  */
  if (sum > 0)
    md5_process_bytes (buffer, sum, &ctx);

  /* Construct result in desired memory.  */
  md5_finish_ctx (&ctx, resblock);
  return 0;
}