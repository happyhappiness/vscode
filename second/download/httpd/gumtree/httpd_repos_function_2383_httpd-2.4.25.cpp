static h2_task *get_latest_repeatable_unsubmitted_task(h2_mplx *m) 
{
    task_iter_ctx ctx;
    ctx.m = m;
    ctx.task = NULL;
    h2_ihash_iter(m->tasks, latest_repeatable_unsubmitted_iter, &ctx);
    return ctx.task;
}