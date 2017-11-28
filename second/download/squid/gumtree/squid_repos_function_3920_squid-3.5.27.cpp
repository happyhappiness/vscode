Adaptation::Answer
Adaptation::Answer::Block(const String &aRule)
{
    Answer answer(akBlock);
    answer.ruleId = aRule;
    debugs(93, 4, HERE << "blocking rule: " << aRule);
    return answer;
}