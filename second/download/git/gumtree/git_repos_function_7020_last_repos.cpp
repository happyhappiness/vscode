static reg_errcode_t
calc_eclosure (re_dfa_t *dfa)
{
  int node_idx, incomplete;
#ifdef DEBUG
  assert (dfa->nodes_len > 0);
#endif
  incomplete = 0;
  /* For each nodes, calculate epsilon closure.  */
  for (node_idx = 0; ; ++node_idx)
    {
      reg_errcode_t err;
      re_node_set eclosure_elem;
      if (node_idx == dfa->nodes_len)
	{
	  if (!incomplete)
	    break;
	  incomplete = 0;
	  node_idx = 0;
	}

#ifdef DEBUG
      assert (dfa->eclosures[node_idx].nelem != -1);
#endif

      /* If we have already calculated, skip it.  */
      if (dfa->eclosures[node_idx].nelem != 0)
	continue;
      /* Calculate epsilon closure of `node_idx'.  */
      err = calc_eclosure_iter (&eclosure_elem, dfa, node_idx, 1);
      if (BE (err != REG_NOERROR, 0))
	return err;

      if (dfa->eclosures[node_idx].nelem == 0)
	{
	  incomplete = 1;
	  re_node_set_free (&eclosure_elem);
	}
    }
  return REG_NOERROR;
}