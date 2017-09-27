}

/*****************************************************************************
 * run-time vhost matching functions
 */

/* Lowercase and remove any trailing dot and/or :port from the hostname,
 * and check that it is sane.
 *
 * In most configurations the exact syntax of the hostname isn't
 * important so strict sanity checking isn't necessary. However, in
 * mass hosting setups (using mod_vhost_alias or mod_rewrite) where
