        // no body
        if (doneWithAdaptation()) // we may still be sending virgin response
            handleAdaptationCompleted();
    }
}

// will not receive adapted response headers (and, hence, body)
void
ServerStateData::noteAdaptationQueryAbort(bool final)
{
    clearAdaptation(adaptedHeadSource);
    handleAdaptationAborted(!final);
}

void
ServerStateData::resumeBodyStorage()
{
    if (abortOnBadEntry("store entry aborted while kick producer callback"))
        return;

