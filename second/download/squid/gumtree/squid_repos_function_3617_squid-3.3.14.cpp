static bool
refreshIsStaleIfHit(const int reason)
{
    switch (reason) {
    case FRESH_MIN_RULE:
    case FRESH_LMFACTOR_RULE:
    case FRESH_EXPIRES:
        return false;
    default:
        return true;
    }
}