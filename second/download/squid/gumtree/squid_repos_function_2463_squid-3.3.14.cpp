void
FwdState::logReplyStatus(int tries, http_status status)
{
    if (status > HTTP_INVALID_HEADER)
        return;

    assert(tries >= 0);

    if (tries > MAX_FWD_STATS_IDX)
        tries = MAX_FWD_STATS_IDX;

    ++ FwdReplyCodes[tries][status];
}