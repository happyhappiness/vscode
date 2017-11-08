static int mutex_needs_file(apr_lockmech_e mech)
{
    if (mech != APR_LOCK_FLOCK
        && mech != APR_LOCK_FCNTL
#if APR_USE_FLOCK_SERIALIZE || APR_USE_FCNTL_SERIALIZE
        && mech != APR_LOCK_DEFAULT
#endif
        ) {
        return 0;
    }
    return 1;
}