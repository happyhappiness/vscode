void
statHistCopy(StatHist * Dest, const StatHist * Orig)
{
    assert(Dest);
    assert(Orig);
    debugs(62, 3, "statHistCopy: Dest=" << Dest << ", Orig=" << Orig);
    assert(Dest->bins);
    /* better be safe than sorry */
    debugs(62, 3, "statHistCopy: capacity " << Dest->capacity << " " << Orig->capacity);
    assert(Dest->capacity == Orig->capacity);
    debugs(62, 3, "statHistCopy: min " << Dest->min << " " << Orig->min  );
    assert(Dest->min == Orig->min);
    debugs(62, 3, "statHistCopy: max " << Dest->max << " " << Orig->max  );
    assert(Dest->max == Orig->max);
    debugs(62, 3, "statHistCopy: scale " << Dest->scale << " " << Orig->scale  );
    assert(fabs(Dest->scale - Orig->scale) < 0.0000001);
    assert(Dest->val_in == Orig->val_in);
    assert(Dest->val_out == Orig->val_out);
    /* actual copy */
    debugs(62, 3, "statHistCopy: copying " <<
           (long int) (Dest->capacity * sizeof(*Dest->bins)) << " bytes to " <<
           Dest->bins << " from " << Orig->bins);

    xmemcpy(Dest->bins, Orig->bins, Dest->capacity * sizeof(*Dest->bins));
}