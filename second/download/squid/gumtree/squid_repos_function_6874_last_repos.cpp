bool
esiSequence::finishedProcessing() const
{
    return nextElementToProcess() >= elements.size();
}