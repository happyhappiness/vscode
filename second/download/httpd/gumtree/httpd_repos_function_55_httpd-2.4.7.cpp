static void setterm(int unused)
{
#ifdef DEBUG
    apr_file_printf(errfile, "interrupt" APR_EOL_STR);
#endif
    interrupted = 1;
}