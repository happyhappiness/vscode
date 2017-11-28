        buf.append("R", 1);

    if (haveConnection() && !doneReading())
        buf.append("r", 1);

    if (!state.doneWriting() && state.writing != State::writingInit)
        buf.appendf("w(%d)", state.writing);

    if (preview.enabled()) {
        if (!preview.done())
            buf.appendf("P(%d)", (int) preview.debt());
    }

    if (virginBodySending.active())
        buf.append("B", 1);

    if (!state.doneParsing() && state.parsing != State::psIcapHeader)
        buf.appendf("p(%d)", state.parsing);

    if (!doneSending() && state.sending != State::sendingUndecided)
        buf.appendf("S(%d)", state.sending);

    if (state.readyForUob)
        buf.append("6", 1);

    if (canStartBypass)
        buf.append("Y", 1);
