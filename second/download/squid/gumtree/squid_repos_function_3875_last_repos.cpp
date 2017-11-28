static std::ostream &
operator <<(std::ostream &os, const Ssl::GeneratorRequest &gr)
{
    return os << "crtGenRq" << gr.query.id.value << "/" << gr.requestors.size();
}