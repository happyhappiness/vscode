static std::ostream &
CurrentException(std::ostream &os)
{
    if (std::current_exception()) {
        try {
            throw; // re-throw to recognize the exception type
        }
        catch (const std::exception &ex) {
            os << ex.what();
        }
        catch (...) {
            os << "[unknown exception type]";
        }
    } else {
        os << "[no active exception]";
    }
    return os;
}