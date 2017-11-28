void
Rock::Rebuild::validationSteps()
{
    debugs(47, 5, sd->index << " validating from " << validationPos);

    // see loadingSteps() for the rationale; TODO: avoid duplication
    const int maxSpentMsec = 50; // keep small: validation does not do I/O
    const timeval loopStart = current_time;

    int validated = 0;
    while (validationPos < dbSlotLimit) {
        validateOneEntry();
        ++validationPos;
        ++validated;

        if (validationPos % 1000 == 0)
            debugs(20, 2, "validated: " << validationPos);

        if (opt_foreground_rebuild)
            continue; // skip "few entries at a time" check below

        getCurrentTime();
        const double elapsedMsec = tvSubMsec(loopStart, current_time);
        if (elapsedMsec > maxSpentMsec || elapsedMsec < 0) {
            debugs(47, 5, "pausing after " << validated << " entries in " <<
                   elapsedMsec << "ms; " << (elapsedMsec/validated) << "ms per entry");
            break;
        }
    }
}