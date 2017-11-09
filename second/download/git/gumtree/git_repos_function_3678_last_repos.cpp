static int upload_pack(void)
{
	struct child_process cld = CHILD_PROCESS_INIT;
	argv_array_pushl(&cld.args, "upload-pack", "--strict", NULL);
	argv_array_pushf(&cld.args, "--timeout=%u", timeout);
	return run_service_command(&cld);
}