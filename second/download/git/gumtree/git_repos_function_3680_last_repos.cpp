static int receive_pack(void)
{
	struct child_process cld = CHILD_PROCESS_INIT;
	argv_array_push(&cld.args, "receive-pack");
	return run_service_command(&cld);
}