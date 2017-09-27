
            /*
             *  On "new-round" flag we just start from the top of
             *  the rewriting ruleset again.
             */
            if (p->flags & RULEFLAG_NEWROUND) {
                goto loop;
            }

            /*
             *  If we are forced to skip N next rules, do it now.
             */
