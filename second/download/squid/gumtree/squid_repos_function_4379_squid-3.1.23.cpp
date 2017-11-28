void
ACLFilledChecklist::checkCallback(allow_t answer)
{
    debugs(28, 5, "ACLFilledChecklist::checkCallback: " << this << " answer=" << answer);

    /* During reconfigure, we can end up not finishing call
     * sequences into the auth code */

    if (auth_user_request) {
        /* the filled_checklist lock */
        AUTHUSERREQUESTUNLOCK(auth_user_request, "ACLFilledChecklist");

        /* it might have been connection based */
        /*
         * DPW 2007-05-08
         * yuck, this make me uncomfortable.  why do this here?
         * ConnStateData will do its own unlocking.
         */
        /* BUG 2827: the connection may also not exist. ie fast ACL tests vs client disconnection. */
        if (conn()) {
            AUTHUSERREQUESTUNLOCK(conn()->auth_user_request, "conn via ACLFilledChecklist");
            conn()->auth_type = AUTH_BROKEN;
        }
    }

    ACLChecklist::checkCallback(answer); // may delete us
}