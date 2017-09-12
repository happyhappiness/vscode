                            _format[_l] = '\0';
                            va_copy(_cpy,ap);
                            current = sdscatvprintf(current,_format,_cpy);
                            interpolated = 1;
                            va_end(_cpy);

                            /* Update current position (note: outer blocks
