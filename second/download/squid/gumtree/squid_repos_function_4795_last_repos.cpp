static inline
std::ostream &
operator <<(std::ostream &os, const Parser::BinaryTokenizerContext *context)
{
    if (context)
        os << context->parent << context->name;
    return os;
}