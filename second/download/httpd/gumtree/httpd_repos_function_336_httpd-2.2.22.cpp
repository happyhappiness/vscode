static dav_error * dav_open_lockdb(request_rec *r, int ro, dav_lockdb **lockdb)
{
    const dav_hooks_locks *hooks = DAV_GET_HOOKS_LOCKS(r);

    if (hooks == NULL) {
        *lockdb = NULL;
        return NULL;
    }

    /* open the thing lazily */
    return (*hooks->open_lockdb)(r, ro, 0, lockdb);
}