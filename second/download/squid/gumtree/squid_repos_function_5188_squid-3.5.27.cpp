void
Rock::Rebuild::steps()
{
    if (loadingPos < dbSlotLimit)
        loadingSteps();
    else
        validationSteps();

    checkpoint();
}