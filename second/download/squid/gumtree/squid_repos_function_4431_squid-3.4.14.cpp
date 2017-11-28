void Ssl::CrtdMessage::composeBody(CrtdMessage::BodyParams const & map, std::string const & other_part)
{
    body.clear();
    for (BodyParams::const_iterator i = map.begin(); i != map.end(); ++i) {
        if (i != map.begin())
            body += "\n";
        body += i->first + "=" + i->second;
    }
    if (!other_part.empty())
        body += '\n' + other_part;
}