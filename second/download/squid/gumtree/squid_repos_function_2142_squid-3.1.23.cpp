void
ServerStateData::noteAdaptationQueryAbort(bool final)
{
    clearAdaptation(adaptedHeadSource);
    handleAdaptationAborted(!final);
}