int FadingCounter::count(int howMany)
{
    Must(howMany >= 0);

    if (delta < 0)
        return total += howMany; // forget nothing

    if (horizon < 1e-3) // (e.g., zero)
        return howMany; // remember nothing

    const double deltas = (current_dtime - lastTime) / delta;
    if (deltas >= precision || current_dtime < lastTime) {
        clear(); // forget all values
    } else {
        // forget stale values, if any
        // fmod() or "current_dtime/delta" will overflow int for small deltas
        const int lastSlot = static_cast<int>(fmod(lastTime, horizon) / delta);
        const int staleSlots = static_cast<int>(deltas);
        for (int i = 0, s = lastSlot + 1; i < staleSlots; ++i, ++s) {
            const int idx = s % precision;
            total -= counters[idx];
            counters[idx] = 0;
            Must(total >= 0);
        }
    }

    // apply new information
    lastTime = current_dtime;
    const int curSlot = static_cast<int>(fmod(lastTime, horizon) / delta);
    counters[curSlot % precision] += howMany;
    total += howMany;
    Must(total >= 0);

    return total;
}