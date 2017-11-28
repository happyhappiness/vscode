Adaptation::Answer
Adaptation::Answer::Forward(HttpMsg *aMsg)
{
    Answer answer(akForward);
    answer.message = aMsg;
    debugs(93, 4, HERE << "forwarding: " << (void*)aMsg);
    return answer;
}