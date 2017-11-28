void
ClientHttpRequest::noteAdaptationAnswer(const Adaptation::Answer &answer)
{
    assert(cbdataReferenceValid(this));		// indicates bug
    clearAdaptation(virginHeadSource);
    assert(!adaptedBodySource);

    switch (answer.kind) {
    case Adaptation::Answer::akForward:
        handleAdaptedHeader(answer.message);
        break;

    case Adaptation::Answer::akBlock:
        handleAdaptationBlock(answer);
        break;

    case Adaptation::Answer::akError:
        handleAdaptationFailure(ERR_DETAIL_CLT_REQMOD_ABORT, !answer.final);
        break;
    }
}