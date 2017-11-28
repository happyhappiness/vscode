void
Adaptation::AccessCheck::start()
{
    AsyncJob::start();

    if (!usedDynamicRules())
        check();
}