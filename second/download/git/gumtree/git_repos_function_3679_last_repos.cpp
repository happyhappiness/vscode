static int upload_archive(void)
{
	struct child_process cld = CHILD_PROCESS_INIT;
	argv_array_push(&cld.args, "upload-archive");
	return run_service_command(&cld);
}