icp_opcode
icpGetCommonOpcode()
{
    /* if store is rebuilding, return a UDP_MISS_NOFETCH */

    if ((StoreController::store_dirs_rebuilding && opt_reload_hit_only) ||
            hit_only_mode_until > squid_curtime) {
        return ICP_MISS_NOFETCH;
    }

    return ICP_ERR;
}