bool Kid::calledExit(int code) const
{
    return calledExit() && (exitStatus() == code);
}