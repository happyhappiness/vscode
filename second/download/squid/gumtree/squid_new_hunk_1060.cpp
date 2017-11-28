        /* Hook into pending lookup */
        state->queue = oldstate->queue;
        oldstate->queue = state;
    } else {
        /* No pending lookup found. Sumbit to helper */

        MemBuf buf;
        buf.init();
        buf.appendf("%s\n", key);
        debugs(82, 4, "externalAclLookup: looking up for '" << key << "' in '" << def->name << "'.");

        if (!def->theHelper->trySubmit(buf.buf, externalAclHandleReply, state)) {
            debugs(82, 7, HERE << "'" << def->name << "' submit to helper failed");
            assert(inBackground); // or the caller should have checked
            delete state;
            return;
        }

        dlinkAdd(state, &state->list, &def->queue);

        buf.clean();
    }

