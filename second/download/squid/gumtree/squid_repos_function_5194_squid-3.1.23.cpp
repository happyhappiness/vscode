bool
BlockingFile::ioInProgress() const
{
    /** \retval false   IO is never pending with UFS */
    return false;
}