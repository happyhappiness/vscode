            // the URL as part of the list. First, gobble all meta data.
            unsigned int offset = addon;
            SquidMetaList meta;
            while ( offset + addon <= datastart ) {
                unsigned int size = 0;
                memcpy( &size, linebuffer+offset+sizeof(char), sizeof(unsigned int) );
                meta.append( SquidMetaType(*(linebuffer+offset)),
                             size, linebuffer+offset+addon );
                offset += ( addon + size );
            }

            // Now extract the key URL from the meta data.
