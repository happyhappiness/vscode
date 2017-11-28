void
CossMemBuf::describe(int level, int line)
{
    debugs(79, level, "membuf " << this << ", LC:" << std::setfill('0') <<
           std::setw(2) << lockcount << ", ST:" <<
           std::setw(10) <<  (unsigned long) diskstart << ", FL:" <<
           (flags.full ? 'F' : '.') << (flags.writing ? 'W' : '.'));
}