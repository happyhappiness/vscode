void h2_task_set_request(h2_task *task, 
                         const char *method, 
                         const char *scheme, 
                         const char *authority, 
                         const char *path, 
                         apr_table_t *headers, int eos)
{
    task->method = method;
    task->scheme = scheme;
    task->authority = authority;
    task->path = path;
    task->headers = headers;
    task->input_eos = eos;
}