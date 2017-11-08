static void
internal_function
update_regs (const re_dfa_t *dfa, regmatch_t *pmatch,
	     regmatch_t *prev_idx_match, int cur_node, int cur_idx, int nmatch)
{
  int type = dfa->nodes[cur_node].type;
  if (type == OP_OPEN_SUBEXP)
    {
      int reg_num = dfa->nodes[cur_node].opr.idx + 1;

      /* We are at the first node of this sub expression.  */
      if (reg_num < nmatch)
	{
	  pmatch[reg_num].rm_so = cur_idx;
	  pmatch[reg_num].rm_eo = -1;
	}
    }
  else if (type == OP_CLOSE_SUBEXP)
    {
      int reg_num = dfa->nodes[cur_node].opr.idx + 1;
      if (reg_num < nmatch)
	{
	  /* We are at the last node of this sub expression.  */
	  if (pmatch[reg_num].rm_so < cur_idx)
	    {
	      pmatch[reg_num].rm_eo = cur_idx;
	      /* This is a non-empty match or we are not inside an optional
		 subexpression.  Accept this right away.  */
	      memcpy (prev_idx_match, pmatch, sizeof (regmatch_t) * nmatch);
	    }
	  else
	    {
	      if (dfa->nodes[cur_node].opt_subexp
		  && prev_idx_match[reg_num].rm_so != -1)
		/* We transited through an empty match for an optional
		   subexpression, like (a?)*, and this is not the subexp's
		   first match.  Copy back the old content of the registers
		   so that matches of an inner subexpression are undone as
		   well, like in ((a?))*.  */
		memcpy (pmatch, prev_idx_match, sizeof (regmatch_t) * nmatch);
	      else
		/* We completed a subexpression, but it may be part of
		   an optional one, so do not update PREV_IDX_MATCH.  */
		pmatch[reg_num].rm_eo = cur_idx;
	    }
	}
    }
}