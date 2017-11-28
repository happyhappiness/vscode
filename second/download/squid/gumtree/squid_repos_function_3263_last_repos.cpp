void
Adaptation::Iterator::noteAdaptationAnswer(const Answer &answer)
{
    switch (answer.kind) {
    case Answer::akForward:
        handleAdaptedHeader(const_cast<HttpMsg*>(answer.message.getRaw()));
        break;

    case Answer::akBlock:
        handleAdaptationBlock(answer);
        break;

    case Answer::akError:
        handleAdaptationError(answer.final);
        break;
    }
}