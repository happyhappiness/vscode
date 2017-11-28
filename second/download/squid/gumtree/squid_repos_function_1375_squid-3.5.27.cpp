void
String::absorb(String &old)
{
    clean();
    setBuffer(old.buf_, old.size_);
    len_ = old.len_;
    old.size_ = 0;
    old.buf_ = NULL;
    old.len_ = 0;
}