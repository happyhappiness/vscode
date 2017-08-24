{
            fprintf ( stderr, "   block %d runs from " MaybeUInt64_FMT 
                              " to " MaybeUInt64_FMT "\n",
                      rbCtr+1,  bStart[currBlock], bEnd[currBlock] );
            rbStart[rbCtr] = bStart[currBlock];
            rbEnd[rbCtr] = bEnd[currBlock];
            rbCtr++;
         }