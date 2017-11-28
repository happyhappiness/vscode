static void
checkFailureRatio(err_type etype, hier_code hcode)
{
    // Can be set at compile time with -D compiler flag
#ifndef FAILURE_MODE_TIME
#define FAILURE_MODE_TIME 300
#endif

    if (hcode == HIER_NONE)
        return;

    // don't bother when ICP is disabled.
    if (Config.Port.icp <= 0)
        return;

    static double magic_factor = 100.0;
    double n_good;
    double n_bad;

    n_good = magic_factor / (1.0 + request_failure_ratio);

    n_bad = magic_factor - n_good;

    switch (etype) {

    case ERR_DNS_FAIL:

    case ERR_CONNECT_FAIL:
    case ERR_SECURE_CONNECT_FAIL:

    case ERR_READ_ERROR:
        ++n_bad;
        break;

    default:
        ++n_good;
    }

    request_failure_ratio = n_bad / n_good;

    if (hit_only_mode_until > squid_curtime)
        return;

    if (request_failure_ratio < 1.0)
        return;

    debugs(33, DBG_CRITICAL, "WARNING: Failure Ratio at "<< std::setw(4)<<
           std::setprecision(3) << request_failure_ratio);

    debugs(33, DBG_CRITICAL, "WARNING: ICP going into HIT-only mode for " <<
           FAILURE_MODE_TIME / 60 << " minutes...");

    hit_only_mode_until = squid_curtime + FAILURE_MODE_TIME;

    request_failure_ratio = 0.8;	/* reset to something less than 1.0 */
}