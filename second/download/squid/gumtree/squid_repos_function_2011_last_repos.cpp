std::ostream &
operator<< (std::ostream &s, HttpHdrCcType c)
{
    const unsigned char ic = static_cast<int>(c);
    if (c < HttpHdrCcType::CC_ENUM_END)
        s << CcAttrs[ic].name << '[' << ic << ']' ;
    else
        s << "*invalid hdrcc* [" << ic << ']';
    return s;
}