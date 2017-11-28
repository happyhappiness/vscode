Adaptation::Answer
Adaptation::Answer::Error(bool final)
{
    Answer answer(akError);
    answer.final = final;
    debugs(93, 4, HERE << "error: " << final);
    return answer;
}