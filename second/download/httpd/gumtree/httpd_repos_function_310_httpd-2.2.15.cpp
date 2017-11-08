static dav_error * dav_validate_resource_state(apr_pool_t *p,
                                               const dav_resource *resource,
                                               dav_lockdb *lockdb,
                                               const dav_if_header *if_header,
                                               int flags,
                                               dav_buffer *pbuf,
                                               request_rec *r)
{
    dav_error *err;
    const char *uri;
    const char *etag;
    const dav_hooks_locks *locks_hooks = (lockdb ? lockdb->hooks : NULL);
    const dav_if_header *ifhdr_scan;
    dav_if_state_list *state_list;
    dav_lock *lock_list;
    dav_lock *lock;
    int num_matched;
    int num_that_apply;
    int seen_locktoken;
    apr_size_t uri_len;
    const char *reason = NULL;

    /* DBG1("validate: <%s>", resource->uri); */

    /*
    ** The resource will have one of three states:
    **
    ** 1) No locks. We have no special requirements that the user supply
    **    specific locktokens. One of the state lists must match, and
    **    we're done.
    **
    ** 2) One exclusive lock. The locktoken must appear *anywhere* in the
    **    If: header. Of course, asserting the token in a "Not" term will
    **    quickly fail that state list :-). If the locktoken appears in
    **    one of the state lists *and* one state list matches, then we're
    **    done.
    **
    ** 3) One or more shared locks. One of the locktokens must appear
    **    *anywhere* in the If: header. If one of the locktokens appears,
    **    and we match one state list, then we are done.
    **
    ** The <seen_locktoken> variable determines whether we have seen one
    ** of this resource's locktokens in the If: header.
    */

    /*
    ** If this is a new lock request, <flags> will contain the requested
    ** lock scope.  Three rules apply:
    **
    ** 1) Do not require a (shared) locktoken to be seen (when we are
    **    applying another shared lock)
    ** 2) If the scope is exclusive and we see any locks, fail.
    ** 3) If the scope is shared and we see an exclusive lock, fail.
    */

    if (lockdb == NULL) {
        /* we're in State 1. no locks. */
        lock_list = NULL;
    }
    else {
        /*
        ** ### hrm... we don't need to have these fully
        ** ### resolved since we're only looking at the
        ** ### locktokens...
        **
        ** ### use get_locks w/ calltype=PARTIAL
        */
        if ((err = dav_lock_query(lockdb, resource, &lock_list)) != NULL) {
            return dav_push_error(p,
                                  HTTP_INTERNAL_SERVER_ERROR, 0,
                                  "The locks could not be queried for "
                                  "verification against a possible \"If:\" "
                                  "header.",
                                  err);
        }

        /* lock_list now determines whether we're in State 1, 2, or 3. */
    }

    /*
    ** For a new, exclusive lock: if any locks exist, fail.
    ** For a new, shared lock:    if an exclusive lock exists, fail.
    **                            else, do not require a token to be seen.
    */
    if (flags & DAV_LOCKSCOPE_EXCLUSIVE) {
        if (lock_list != NULL) {
            return dav_new_error(p, HTTP_LOCKED, 0,
                                 "Existing lock(s) on the requested resource "
                                 "prevent an exclusive lock.");
        }

        /*
        ** There are no locks, so we can pretend that we've already met
        ** any requirement to find the resource's locks in an If: header.
        */
        seen_locktoken = 1;
    }
    else if (flags & DAV_LOCKSCOPE_SHARED) {
        /*
        ** Strictly speaking, we don't need this loop. Either the first
        ** (and only) lock will be EXCLUSIVE, or none of them will be.
        */
        for (lock = lock_list; lock != NULL; lock = lock->next) {
            if (lock->scope == DAV_LOCKSCOPE_EXCLUSIVE) {
                return dav_new_error(p, HTTP_LOCKED, 0,
                                     "The requested resource is already "
                                     "locked exclusively.");
            }
        }

        /*
        ** The locks on the resource (if any) are all shared. Set the
        ** <seen_locktoken> flag to indicate that we do not need to find
        ** the locks in an If: header.
        */
        seen_locktoken = 1;
    }
    else {
        /*
        ** For methods other than LOCK:
        **
        ** If we have no locks, then <seen_locktoken> can be set to true --
        ** pretending that we've already met the requirement of seeing one
        ** of the resource's locks in the If: header.
        **
        ** Otherwise, it must be cleared and we'll look for one.
        */
        seen_locktoken = (lock_list == NULL);
    }

    /*
    ** If there is no If: header, then we can shortcut some logic:
    **
    ** 1) if we do not need to find a locktoken in the (non-existent) If:
    **    header, then we are successful.
    **
    ** 2) if we must find a locktoken in the (non-existent) If: header, then
    **    we fail.
    */
    if (if_header == NULL) {
        if (seen_locktoken)
            return NULL;

        return dav_new_error(p, HTTP_LOCKED, 0,
                             "This resource is locked and an \"If:\" header "
                             "was not supplied to allow access to the "
                             "resource.");
    }
    /* the If: header is present */

    /*
    ** If a dummy header is present (because of a Lock-Token: header), then
    ** we are required to find that token in this resource's set of locks.
    ** If we have no locks, then we immediately fail.
    **
    ** This is a 400 (Bad Request) since they should only submit a locktoken
    ** that actually exists.
    **
    ** Don't issue this response if we're talking about the parent resource.
    ** It is okay for that resource to NOT have this locktoken.
    ** (in fact, it certainly will not: a dummy_header only occurs for the
    **  UNLOCK method, the parent is checked only for locknull resources,
    **  and the parent certainly does not have the (locknull's) locktoken)
    */
    if (lock_list == NULL && if_header->dummy_header) {
        if (flags & DAV_VALIDATE_IS_PARENT)
            return NULL;
        return dav_new_error(p, HTTP_BAD_REQUEST, 0,
                             "The locktoken specified in the \"Lock-Token:\" "
                             "header is invalid because this resource has no "
                             "outstanding locks.");
    }

    /*
    ** Prepare the input URI. We want the URI to never have a trailing slash.
    **
    ** When URIs are placed into the dav_if_header structure, they are
    ** guaranteed to never have a trailing slash. If the URIs are equivalent,
    ** then it doesn't matter if they both lack a trailing slash -- they're
    ** still equivalent.
    **
    ** Note: we could also ensure that a trailing slash is present on both
    ** URIs, but the majority of URIs provided to us via a resource walk
    ** will not contain that trailing slash.
    */
    uri = resource->uri;
    uri_len = strlen(uri);
    if (uri[uri_len - 1] == '/') {
        dav_set_bufsize(p, pbuf, uri_len);
        memcpy(pbuf->buf, uri, uri_len);
        pbuf->buf[--uri_len] = '\0';
        uri = pbuf->buf;
    }

    /* get the resource's etag; we may need it during the checks */
    etag = (*resource->hooks->getetag)(resource);

    /* how many state_lists apply to this URI? */
    num_that_apply = 0;

    /* If there are if-headers, fail if this resource
     * does not match at least one state_list.
     */
    for (ifhdr_scan = if_header;
         ifhdr_scan != NULL;
         ifhdr_scan = ifhdr_scan->next) {

        /* DBG2("uri=<%s>  if_uri=<%s>", uri, ifhdr_scan->uri ? ifhdr_scan->uri : "(no uri)"); */

        if (ifhdr_scan->uri != NULL
            && (uri_len != ifhdr_scan->uri_len
                || memcmp(uri, ifhdr_scan->uri, uri_len) != 0)) {
            /*
            ** A tagged-list's URI doesn't match this resource's URI.
            ** Skip to the next state_list to see if it will match.
            */
            continue;
        }

        /* this state_list applies to this resource */

        /*
        ** ### only one state_list should ever apply! a no-tag, or a tagged
        ** ### where S9.4.2 states only one can match.
        **
        ** ### revamp this code to loop thru ifhdr_scan until we find the
        ** ### matching state_list. process it. stop.
        */
        ++num_that_apply;

        /* To succeed, resource must match *all* of the states
         * specified in the state_list.
         */
        for (state_list = ifhdr_scan->state;
             state_list != NULL;
             state_list = state_list->next) {

            switch(state_list->type) {
            case dav_if_etag:
            {
                const char *given_etag, *current_etag;
                int mismatch;

                /* Do a weak entity comparison function as defined in
                 * RFC 2616 13.3.3.
                 */
                if (state_list->etag[0] == 'W' &&
                    state_list->etag[1] == '/') {
                    given_etag = state_list->etag + 2;
                }
                else {
                    given_etag = state_list->etag;
                }
                if (etag[0] == 'W' &&
                    etag[1] == '/') {
                    current_etag = etag + 2;
                }
                else {
                    current_etag = etag;
                }

                mismatch = strcmp(given_etag, current_etag);

                if (state_list->condition == DAV_IF_COND_NORMAL && mismatch) {
                    /*
                    ** The specified entity-tag does not match the
                    ** entity-tag on the resource. This state_list is
                    ** not going to match. Bust outta here.
                    */
                    reason =
                        "an entity-tag was specified, but the resource's "
                        "actual ETag does not match.";
                    goto state_list_failed;
                }
                else if (state_list->condition == DAV_IF_COND_NOT
                         && !mismatch) {
                    /*
                    ** The specified entity-tag DOES match the
                    ** entity-tag on the resource. This state_list is
                    ** not going to match. Bust outta here.
                    */
                    reason =
                        "an entity-tag was specified using the \"Not\" form, "
                        "but the resource's actual ETag matches the provided "
                        "entity-tag.";
                    goto state_list_failed;
                }
                break;
            }

            case dav_if_opaquelock:
                if (lockdb == NULL) {
                    if (state_list->condition == DAV_IF_COND_NOT) {
                        /* the locktoken is definitely not there! (success) */
                        continue;
                    }

                    /* condition == DAV_IF_COND_NORMAL */

                    /*
                    ** If no lockdb is provided, then validation fails for
                    ** this state_list (NORMAL means we were supposed to
                    ** find the token, which we obviously cannot do without
                    ** a lock database).
                    **
                    ** Go and try the next state list.
                    */
                    reason =
                        "a State-token was supplied, but a lock database "
                        "is not available for to provide the required lock.";
                    goto state_list_failed;
                }

                /* Resource validation 'fails' if:
                 *    ANY  of the lock->locktokens match
                 *         a NOT state_list->locktoken,
                 * OR
                 *    NONE of the lock->locktokens match
                 *         a NORMAL state_list->locktoken.
                 */
                num_matched = 0;
                for (lock = lock_list; lock != NULL; lock = lock->next) {

                    /*
                    DBG2("compare: rsrc=%s  ifhdr=%s",
                         (*locks_hooks->format_locktoken)(p, lock->locktoken),
                         (*locks_hooks->format_locktoken)(p, state_list->locktoken));
                    */

                    /* nothing to do if the locktokens do not match. */
                    if ((*locks_hooks->compare_locktoken)(state_list->locktoken, lock->locktoken)) {
                        continue;
                    }

                    /*
                    ** We have now matched up one of the resource's locktokens
                    ** to a locktoken in a State-token in the If: header.
                    ** Note this fact, so that we can pass the overall
                    ** requirement of seeing at least one of the resource's
                    ** locktokens.
                    */
                    seen_locktoken = 1;

                    if (state_list->condition == DAV_IF_COND_NOT) {
                        /*
                        ** This state requires that the specified locktoken
                        ** is NOT present on the resource. But we just found
                        ** it. There is no way this state-list can now
                        ** succeed, so go try another one.
                        */
                        reason =
                            "a State-token was supplied, which used a "
                            "\"Not\" condition. The State-token was found "
                            "in the locks on this resource";
                        goto state_list_failed;
                    }

                    /* condition == DAV_IF_COND_NORMAL */

                    /* Validate auth_user:  If an authenticated user created
                    ** the lock, only the same user may submit that locktoken
                    ** to manipulate a resource.
                    */
                    if (lock->auth_user &&
                        (!r->user ||
                         strcmp(lock->auth_user, r->user))) {
                        const char *errmsg;

                        errmsg = apr_pstrcat(p, "User \"",
                                            r->user,
                                            "\" submitted a locktoken created "
                                            "by user \"",
                                            lock->auth_user, "\".", NULL);
                        return dav_new_error(p, HTTP_FORBIDDEN, 0, errmsg);
                    }

                    /*
                    ** We just matched a specified State-Token to one of the
                    ** resource's locktokens.
                    **
                    ** Break out of the lock scan -- we only needed to find
                    ** one match (actually, there shouldn't be any other
                    ** matches in the lock list).
                    */
                    num_matched = 1;
                    break;
                }

                if (num_matched == 0
                    && state_list->condition == DAV_IF_COND_NORMAL) {
                    /*
                    ** We had a NORMAL state, meaning that we should have
                    ** found the State-Token within the locks on this
                    ** resource. We didn't, so this state_list must fail.
                    */
                    reason =
                        "a State-token was supplied, but it was not found "
                        "in the locks on this resource.";
                    goto state_list_failed;
                }

                break;

            case dav_if_unknown:
                /* Request is predicated on some unknown state token,
                 * which must be presumed to *not* match, so fail
                 * unless this is a Not condition. */

                if (state_list->condition == DAV_IF_COND_NORMAL) {
                    reason =
                        "an unknown state token was supplied";
                    goto state_list_failed;
                }
                break;

            } /* switch */
        } /* foreach ( state_list ) */

        /*
        ** We've checked every state in this state_list and none of them
        ** have failed. Since all of them succeeded, then we have a matching
        ** state list and we may be done.
        **
        ** The next requirement is that we have seen one of the resource's
        ** locktokens (if any). If we have, then we can just exit. If we
        ** haven't, then we need to keep looking.
        */
        if (seen_locktoken) {
            /* woo hoo! */
            return NULL;
        }

        /*
        ** Haven't seen one. Let's break out of the search and just look
        ** for a matching locktoken.
        */
        break;

        /*
        ** This label is used when we detect that a state_list is not
        ** going to match this resource. We bust out and try the next
        ** state_list.
        */
      state_list_failed:
        ;

    } /* foreach ( ifhdr_scan ) */

    /*
    ** The above loop exits for one of two reasons:
    **   1) a state_list matched and seen_locktoken is false.
    **   2) all if_header structures were scanned, without (1) occurring
    */

    if (ifhdr_scan == NULL) {
        /*
        ** We finished the loop without finding any matching state lists.
        */

        /*
        ** If none of the state_lists apply to this resource, then we
        ** may have succeeded. Note that this scenario implies a
        ** tagged-list with no matching state_lists. If the If: header
        ** was a no-tag-list, then it would have applied to this resource.
        **
        ** S9.4.2 states that when no state_lists apply, then the header
        ** should be ignored.
        **
        ** If we saw one of the resource's locktokens, then we're done.
        ** If we did not see a locktoken, then we fail.
        */
        if (num_that_apply == 0) {
            if (seen_locktoken)
                return NULL;

            /*
            ** We may have aborted the scan before seeing the locktoken.
            ** Rescan the If: header to see if we can find the locktoken
            ** somewhere.
            **
            ** Note that seen_locktoken == 0 implies lock_list != NULL
            ** which implies locks_hooks != NULL.
            */
            if (dav_find_submitted_locktoken(if_header, lock_list,
                                             locks_hooks)) {
                /*
                ** We found a match! We're set... none of the If: header
                ** assertions apply (implicit success), and the If: header
                ** specified the locktoken somewhere. We're done.
                */
                return NULL;
            }

            return dav_new_error(p, HTTP_LOCKED, 0 /* error_id */,
                                 "This resource is locked and the \"If:\" "
                                 "header did not specify one of the "
                                 "locktokens for this resource's lock(s).");
        }
        /* else: one or more state_lists were applicable, but failed. */

        /*
        ** If the dummy_header did not match, then they specified an
        ** incorrect token in the Lock-Token header. Forget whether the
        ** If: statement matched or not... we'll tell them about the
        ** bad Lock-Token first. That is considered a 400 (Bad Request).
        */
        if (if_header->dummy_header) {
            return dav_new_error(p, HTTP_BAD_REQUEST, 0,
                                 "The locktoken specified in the "
                                 "\"Lock-Token:\" header did not specify one "
                                 "of this resource's locktoken(s).");
        }

        if (reason == NULL) {
            return dav_new_error(p, HTTP_PRECONDITION_FAILED, 0,
                                 "The preconditions specified by the \"If:\" "
                                 "header did not match this resource.");
        }

        return dav_new_error(p, HTTP_PRECONDITION_FAILED, 0,
                             apr_psprintf(p,
                                         "The precondition(s) specified by "
                                         "the \"If:\" header did not match "
                                         "this resource. At least one "
                                         "failure is because: %s", reason));
    }

    /* assert seen_locktoken == 0 */

    /*
    ** ifhdr_scan != NULL implies we found a matching state_list.
    **
    ** Since we're still here, it also means that we have not yet found
    ** one the resource's locktokens in the If: header.
    **
    ** Scan all the if_headers and states looking for one of this
    ** resource's locktokens. Note that we need to go back and scan them
    ** all -- we may have aborted a scan with a failure before we saw a
    ** matching token.
    **
    ** Note that seen_locktoken == 0 implies lock_list != NULL which implies
    ** locks_hooks != NULL.
    */
    if (dav_find_submitted_locktoken(if_header, lock_list, locks_hooks)) {
        /*
        ** We found a match! We're set... we have a matching state list,
        ** and the If: header specified the locktoken somewhere. We're done.
        */
        return NULL;
    }

    /*
    ** We had a matching state list, but the user agent did not specify one
    ** of this resource's locktokens. Tell them so.
    **
    ** Note that we need to special-case the message on whether a "dummy"
    ** header exists. If it exists, yet we didn't see a needed locktoken,
    ** then that implies the dummy header (Lock-Token header) did NOT
    ** specify one of this resource's locktokens. (this implies something
    ** in the real If: header matched)
    **
    ** We want to note the 400 (Bad Request) in favor of a 423 (Locked).
    */
    if (if_header->dummy_header) {
        return dav_new_error(p, HTTP_BAD_REQUEST, 0,
                             "The locktoken specified in the "
                             "\"Lock-Token:\" header did not specify one "
                             "of this resource's locktoken(s).");
    }

    return dav_new_error(p, HTTP_LOCKED, 1 /* error_id */,
                         "This resource is locked and the \"If:\" header "
                         "did not specify one of the "
                         "locktokens for this resource's lock(s).");
}