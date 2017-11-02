__END_DECLS

/* Configure File Devices */

void GUSISetupDevices()
{
#ifdef GUSISetupDevices_BeginHook
	GUSISetupDevices_BeginHook
#endif
	GUSIwithNullSockets();
#ifdef GUSISetupDevices_EndHook
	GUSISetupDevices_EndHook
#endif
}