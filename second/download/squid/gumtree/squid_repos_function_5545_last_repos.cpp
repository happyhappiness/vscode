time_t
Comm::Connection::timeLeft(const time_t idleTimeout) const
{
    if (!Config.Timeout.pconnLifetime)
        return idleTimeout;

    const time_t lifeTimeLeft = lifeTime() < Config.Timeout.pconnLifetime ? Config.Timeout.pconnLifetime - lifeTime() : 1;
    return min(lifeTimeLeft, idleTimeout);
}