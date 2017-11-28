/* some uint8_t do not like streaming control-chars (values 0-31, 127+) */
inline std::ostream& operator <<(std::ostream &os, const uint8_t d)
{
    return (os << (int)d);
}

#endif /* SQUID_DEBUG_H */
