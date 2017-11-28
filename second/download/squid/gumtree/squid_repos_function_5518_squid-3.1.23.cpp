void
esiSequence::processStep(int dovars)
{
    size_t elementToProcess = nextElementToProcess();
    nextElementToProcess(elementToProcess + 1);
    esiProcessResult_t tempResult = processOne(dovars, elementToProcess);

    if (processingResult < tempResult) {
        debugs(86, 5, "esiSequence::process: processingResult was " << processingResult << ", increasing to " << tempResult);
        processingResult = tempResult;
    }
}