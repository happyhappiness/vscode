static void FinalShutdownRunners(void *) {
        RunRegisteredHere(RegisteredRunner::endingShutdown);

        // XXX: this should be a Runner.
#if USE_AUTH
        /* detach the auth components (only do this on full shutdown) */
        Auth::Scheme::FreeAll();
#endif

        eventAdd("SquidTerminate", &StopEventLoop, NULL, 0, 1, false);
    }