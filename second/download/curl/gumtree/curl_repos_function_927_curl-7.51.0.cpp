__END_DECLS

/* Configure Socket Factories */

void GUSISetupFactories()
{
#ifdef GUSISetupFactories_BeginHook
	GUSISetupFactories_BeginHook
#endif
	GUSIwithInetSockets();
#ifdef GUSISetupFactories_EndHook
	GUSISetupFactories_EndHook
#endif
}