static void cleanup_tempfile_and_exit(int rc)
{
    if (tfp) {
        apr_file_close(tfp);
    }
    exit(rc);
}