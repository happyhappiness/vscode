void Ssl::CrtdMessage::clear()
{
    body_size = 0;
    state = BEFORE_CODE;
    body.clear();
    code.clear();
    current_block.clear();
}