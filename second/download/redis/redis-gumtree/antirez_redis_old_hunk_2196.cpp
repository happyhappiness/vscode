    addReply(c,shared.ok);
}

/* -----------------------------------------------------------------------------
 * Cluster functions related to serving / redirecting clients
 * -------------------------------------------------------------------------- */

/* Return the pointer to the cluster node that is able to serve the command.
 * For the function to succeed the command should only target a single
