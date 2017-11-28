void
Adaptation::Iterator::noteAdaptationAnswer(const Answer &answer)
{
    switch (answer.kind) {
    case Answer::akForward:
        handleAdaptedHeader(answer.message);
        break;

    case Answer::akBlock:
        handleAdaptationBlock(answer);
        break;

    case Answer::akError:
        handleAdaptationError(answer.final);
        break;
    }
}