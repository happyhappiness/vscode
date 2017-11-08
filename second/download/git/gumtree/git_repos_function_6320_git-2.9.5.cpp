static int
internal_function
pop_fail_stack (struct re_fail_stack_t *fs, int *pidx, int nregs,
		regmatch_t *regs, re_node_set *eps_via_nodes)
{
  int num = --fs->num;
  assert (num >= 0);
  *pidx = fs->stack[num].idx;
  memcpy (regs, fs->stack[num].regs, sizeof (regmatch_t) * nregs);
  re_node_set_free (eps_via_nodes);
  re_free (fs->stack[num].regs);
  *eps_via_nodes = fs->stack[num].eps_via_nodes;
  return fs->stack[num].node;
}