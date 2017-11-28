void Adaptation::Initiate::sendAnswer(HttpMsg *msg)
{
    assert(msg);
    AsyncCall::Pointer call = new AnswerCall("Initiator::noteAdaptationAnswer",
            AnswerDialer(theInitiator, &Initiator::noteAdaptationAnswer, msg));
    ScheduleCallHere(call);
    clearInitiator();
}