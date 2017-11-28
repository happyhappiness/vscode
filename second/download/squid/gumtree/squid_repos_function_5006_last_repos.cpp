void
Rock::Rebuild::steps()
{
    if (!doneLoading())
        loadingSteps();
    else
        validationSteps();

    checkpoint();
}