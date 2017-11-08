static reg_errcode_t
internal_function
free_fail_stack_return (struct re_fail_stack_t *fs)
{
  if (fs)
    {
      int fs_idx;
      for (fs_idx = 0; fs_idx < fs->num; ++fs_idx)
	{
	  re_node_set_free (&fs->stack[fs_idx].eps_via_nodes);
	  re_free (fs->stack[fs_idx].regs);
	}
      re_free (fs->stack);
    }
  return REG_NOERROR;
}