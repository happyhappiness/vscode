void Adaptation::Icap::Launcher::noteAdaptationAnswer(const Answer &answer)
{
    debugs(93,5, HERE << "launches: " << theLaunches << " answer: " << answer);

    // XXX: akError is unused by ICAPXaction in favor of noteXactAbort()
    Must(answer.kind != Answer::akError);

    sendAnswer(answer);
    clearAdaptation(theXaction);
    Must(done());
}