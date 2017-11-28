void
RunRegistered(const RegisteredRunner::Method &event)
{
    if (Runners *runners = FindRunners()) {
        // Many things may happen during the loop below. We copy to withstand
        // runner removal/addition and avoid surprises due to registrations from
        // parent constructors (with a half-baked "this"!). This copy also
        // simplifies overall RR logic as it guarantees that registering a
        // runner during event X loop does not execute runner::X().
        Runners oldRunners(*runners);
        for (auto runner: oldRunners) {
            if (runners->find(runner) != runners->end()) // still registered
                (runner->*event)();
        }
    }

    if (event != &RegisteredRunner::finishShutdown)
        return;

    // this is the last event; delete registry-dependent runners (and only them)
    if (Runners *runners = FindRunners()) {
        RunnersGone = true;
        TheRunners = nullptr;
        // from now on, no runners can be registered or unregistered
        for (auto runner: *runners)
            GetRidOfRunner(runner); // leaves a dangling pointer in runners
        delete runners;
    }
}