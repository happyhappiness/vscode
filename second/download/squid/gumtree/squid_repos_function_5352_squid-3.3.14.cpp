AsyncJob::Pointer AsyncJob::Start(AsyncJob *j)
{
    AsyncJob::Pointer job(j);
    CallJobHere(93, 5, job, AsyncJob, start);
    return job;
}