void
EventLoop::setPrimaryEngine(AsyncEngine * engine)
{
    for (engine_vector::iterator i = engines.begin();
            i != engines.end(); ++i)
        if (*i == engine) {
            primaryEngine = engine;
            return;
        }

    fatal("EventLoop::setPrimaryEngine: No such engine!.");
}