void
File::lock(const FileOpeningConfig &cfg)
{
    unsigned int attemptsLeft = cfg.lockAttempts;
    while (attemptsLeft) {
        try {
            --attemptsLeft;
            return lockOnce(cfg);
        } catch (const std::exception &ex) {
            if (!attemptsLeft)
                throw;
            debugs(54, 4, "sleeping and then trying up to " << attemptsLeft <<
                   " more time(s) after a failure: " << ex.what());
        }
        Must(attemptsLeft); // the catch statement handles the last attempt
        xusleep(cfg.RetryGapUsec);
    }
    debugs(54, 9, "disabled");
}