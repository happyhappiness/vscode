void
Adaptation::AccessCheck::start()
{
    AsyncJob::start();
    check();
}