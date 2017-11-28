CharacterSet &
CharacterSet::addRange(unsigned char low, unsigned char high)
{
    //manual loop splitting is needed to cover case where high is 255
    // otherwise low will wrap, resulting in infinite loop
    while (low < high) {
        chars_[static_cast<uint8_t>(low)] = 1;
        ++low;
    }
    chars_[static_cast<uint8_t>(high)] = 1;
    return *this;
}