void module_register (void)
{
#if SWAP_HAVE_READ
	plugin_register_init ("swap", swap_init);
	plugin_register_read ("swap", swap_read);
#endif /* SWAP_HAVE_READ */
}