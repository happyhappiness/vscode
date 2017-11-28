void
EventLoop::registerEngine(AsyncEngine *engine)
{
    engines.push_back(engine);
}