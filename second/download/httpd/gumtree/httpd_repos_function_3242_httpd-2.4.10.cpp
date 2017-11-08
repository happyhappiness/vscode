static apr_status_t cfg_getch(char *ch, void *param)
{
    return apr_file_getc(ch, param);
}