    if (!state.doneParsing() && state.parsing != State::psIcapHeader)
        buf.Printf("p(%d)", state.parsing);

    if (!doneSending() && state.sending != State::sendingUndecided)
        buf.Printf("S(%d)", state.sending);

    if (canStartBypass)
        buf.append("Y", 1);

    if (protectGroupBypass)
        buf.append("G", 1);
}
