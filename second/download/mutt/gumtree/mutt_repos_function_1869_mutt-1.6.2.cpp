static void print_gss_error(OM_uint32 err_maj, OM_uint32 err_min)
{
	OM_uint32 maj_stat, min_stat; 
	OM_uint32 msg_ctx = 0;
	gss_buffer_desc status_string;
	char buf_maj[512];
	char buf_min[512];
	
	do
	{
		maj_stat = gss_display_status (&min_stat,
					       err_maj,
					       GSS_C_GSS_CODE,
					       GSS_C_NO_OID,
					       &msg_ctx,
					       &status_string);
		if (GSS_ERROR(maj_stat))
			break;
		strncpy(buf_maj, (char*) status_string.value, sizeof(buf_maj));
		gss_release_buffer(&min_stat, &status_string);
		
		maj_stat = gss_display_status (&min_stat,
					       err_min,
					       GSS_C_MECH_CODE,
					       GSS_C_NULL_OID,
					       &msg_ctx,
					       &status_string);
		if (!GSS_ERROR(maj_stat))
		{
			strncpy(buf_min, (char*) status_string.value, sizeof(buf_min));
			gss_release_buffer(&min_stat, &status_string);
		}
	} while (!GSS_ERROR(maj_stat) && msg_ctx != 0);
	
	dprint (2, (debugfile, "((%s:%d )(%s:%d))", buf_maj, err_maj, buf_min, err_min));
}