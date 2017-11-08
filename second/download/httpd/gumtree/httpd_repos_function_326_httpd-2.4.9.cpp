static int dav_find_submitted_locktoken(const dav_if_header *if_header,
                                        const dav_lock *lock_list,
                                        const dav_hooks_locks *locks_hooks)
{
    for (; if_header != NULL; if_header = if_header->next) {
        const dav_if_state_list *state_list;

        for (state_list = if_header->state;
             state_list != NULL;
             state_list = state_list->next) {

            if (state_list->type == dav_if_opaquelock) {
                const dav_lock *lock;

                /* given state_list->locktoken, match it */

                /*
                ** The resource will have one or more lock tokens. We only
                ** need to match one of them against any token in the
                ** If: header.
                **
                ** One token case: It is an exclusive or shared lock. Either
                **                 way, we must find it.
                **
                ** N token case: They are shared locks. By policy, we need
                **               to match only one. The resource's other
                **               tokens may belong to somebody else (so we
                **               shouldn't see them in the If: header anyway)
                */
                for (lock = lock_list; lock != NULL; lock = lock->next) {

                    if (!(*locks_hooks->compare_locktoken)(state_list->locktoken, lock->locktoken)) {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}