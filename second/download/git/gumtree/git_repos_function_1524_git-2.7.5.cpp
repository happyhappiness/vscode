void xdiff_clear_find_func(xdemitconf_t *xecfg)
{
	if (xecfg->find_func) {
		int i;
		struct ff_regs *regs = xecfg->find_func_priv;

		for (i = 0; i < regs->nr; i++)
			regfree(&regs->array[i].re);
		free(regs->array);
		free(regs);
		xecfg->find_func = NULL;
		xecfg->find_func_priv = NULL;
	}
}