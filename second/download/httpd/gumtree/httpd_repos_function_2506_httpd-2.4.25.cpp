static apr_status_t output_finish(h2_task *task)
{
    if (!task->output.opened) {
        return open_output(task);
    }
    return APR_SUCCESS;
}