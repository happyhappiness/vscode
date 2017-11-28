    const int rockDirs = Config.cacheSwap.n_strands;

    const bool needCoord = Config.workers > 1 || rockDirs > 0;
    return (needCoord ? 1 : 0) + Config.workers + rockDirs;
}

SBuf
ProcessRoles()
{
    SBuf roles;
    if (IamMasterProcess())
        roles.append(" master");
    if (IamCoordinatorProcess())
        roles.append(" coordinator");
    if (IamWorkerProcess())
        roles.append(" worker");
    if (IamDiskProcess())
        roles.append(" disker");
    return roles;
}

/* A little piece of glue for odd systems */
#ifndef RLIMIT_NOFILE
#ifdef RLIMIT_OFILE
#define RLIMIT_NOFILE RLIMIT_OFILE
#endif
#endif
