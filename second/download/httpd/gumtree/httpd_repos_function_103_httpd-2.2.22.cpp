static void interrupted(void)
{
    apr_file_printf(errfile, "Interrupted.\n");
    cleanup_tempfile_and_exit(1);
}