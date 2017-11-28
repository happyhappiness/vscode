void
FwdState::logReplyStatus(int tries, const Http::StatusCode status)
{
    if (status > Http::scInvalidHeader)
        return;

    assert(tries >= 0);

    if (tries > MAX_FWD_STATS_IDX)
        tries = MAX_FWD_STATS_IDX;

    ++ FwdReplyCodes[tries][status];
}