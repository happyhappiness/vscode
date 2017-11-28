File &
File::operator = (File &&other)
{
    std::swap(fd_, other.fd_);
    return *this;
}