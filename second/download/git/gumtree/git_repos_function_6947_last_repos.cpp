static reg_errcode_t
internal_function
push_fail_stack (struct re_fail_stack_t *fs, int str_idx, int dest_node,
		 int nregs, regmatch_t *regs, re_node_set *eps_via_nodes)
{
  reg_errcode_t err;
  int num = fs->num++;
  if (fs->num == fs->alloc)
    {
      struct re_fail_stack_ent_t *new_array;
      new_array = realloc (fs->stack, (sizeof (struct re_fail_stack_ent_t)
				       * fs->alloc * 2));
      if (new_array == NULL)
	return REG_ESPACE;
      fs->alloc *= 2;
      fs->stack = new_array;
    }
  fs->stack[num].idx = str_idx;
  fs->stack[num].node = dest_node;
  fs->stack[num].regs = re_malloc (regmatch_t, nregs);
  if (fs->stack[num].regs == NULL)
    return REG_ESPACE;
  memcpy (fs->stack[num].regs, regs, sizeof (regmatch_t) * nregs);
  err = re_node_set_init_copy (&fs->stack[num].eps_via_nodes, eps_via_nodes);
  return err;
}