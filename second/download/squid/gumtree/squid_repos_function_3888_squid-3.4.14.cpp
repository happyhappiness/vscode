void Adaptation::Initiate::sendAnswer(const Answer &answer)
{
    AsyncCall::Pointer call = new AnswerCall("Initiator::noteAdaptationAnswer",
            AnswerDialer(theInitiator, &Initiator::noteAdaptationAnswer, answer));
    ScheduleCallHere(call);
    clearInitiator();
}