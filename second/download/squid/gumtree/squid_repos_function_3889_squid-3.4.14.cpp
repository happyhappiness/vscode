void Adaptation::Initiate::tellQueryAborted(bool final)
{
    sendAnswer(Answer::Error(final));
}