        // no body
        if (doneWithAdaptation()) // we may still be sending virgin response
            handleAdaptationCompleted();
    }
}

void
ServerStateData::resumeBodyStorage()
{
    if (abortOnBadEntry("store entry aborted while kick producer callback"))
        return;

