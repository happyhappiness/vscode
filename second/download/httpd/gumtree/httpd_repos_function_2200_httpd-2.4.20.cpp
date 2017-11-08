static int ser_header(void *ctx, const char *name, const char *value) 
{
    h2_task_input *input = (h2_task_input*)ctx;
    apr_brigade_printf(input->bb, NULL, NULL, "%s: %s\r\n", name, value);
    return 1;
}