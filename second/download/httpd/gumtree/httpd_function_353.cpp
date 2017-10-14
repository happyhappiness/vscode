static void interrupted(void)
{
    fprintf(stderr, "Interrupted.\n");
    if (tfp) {
        apr_file_close(tfp);
    }
    exit(1);
}