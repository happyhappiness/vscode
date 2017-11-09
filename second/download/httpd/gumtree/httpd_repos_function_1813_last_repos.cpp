static apr_status_t cleanup_script(void *vptr)
{
    struct cleanup_script_info *info = vptr;
    return cleanup_nonchild_process(info->r, info->pid);
}