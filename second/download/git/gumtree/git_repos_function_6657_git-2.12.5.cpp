static unsigned
re_copy_regs (struct re_registers *regs,
	      regmatch_t *pmatch,
	      int nregs, int regs_allocated)
{
  int rval = REGS_REALLOCATE;
  int i;
  int need_regs = nregs + 1;
  /* We need one extra element beyond `num_regs' for the `-1' marker GNU code
     uses.  */

  /* Have the register data arrays been allocated?  */
  if (regs_allocated == REGS_UNALLOCATED)
    { /* No.  So allocate them with malloc.  */
      regs->start = re_malloc (regoff_t, need_regs);
      if (BE (regs->start == NULL, 0))
	return REGS_UNALLOCATED;
      regs->end = re_malloc (regoff_t, need_regs);
      if (BE (regs->end == NULL, 0))
	{
	  re_free (regs->start);
	  return REGS_UNALLOCATED;
	}
      regs->num_regs = need_regs;
    }
  else if (regs_allocated == REGS_REALLOCATE)
    { /* Yes.  If we need more elements than were already
	 allocated, reallocate them.  If we need fewer, just
	 leave it alone.  */
      if (BE (need_regs > regs->num_regs, 0))
	{
	  regoff_t *new_start = re_realloc (regs->start, regoff_t, need_regs);
	  regoff_t *new_end;
	  if (BE (new_start == NULL, 0))
	    return REGS_UNALLOCATED;
	  new_end = re_realloc (regs->end, regoff_t, need_regs);
	  if (BE (new_end == NULL, 0))
	    {
	      re_free (new_start);
	      return REGS_UNALLOCATED;
	    }
	  regs->start = new_start;
	  regs->end = new_end;
	  regs->num_regs = need_regs;
	}
    }
  else
    {
      assert (regs_allocated == REGS_FIXED);
      /* This function may not be called with REGS_FIXED and nregs too big.  */
      assert (regs->num_regs >= nregs);
      rval = REGS_FIXED;
    }

  /* Copy the regs.  */
  for (i = 0; i < nregs; ++i)
    {
      regs->start[i] = pmatch[i].rm_so;
      regs->end[i] = pmatch[i].rm_eo;
    }
  for ( ; i < regs->num_regs; ++i)
    regs->start[i] = regs->end[i] = -1;

  return rval;
}