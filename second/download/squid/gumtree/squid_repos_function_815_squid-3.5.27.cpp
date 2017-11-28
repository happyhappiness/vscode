void FadingCounter::configure(double newHorizon)
{
    if (fabs(newHorizon - horizon) >= 1e-3) { // diff exceeds one millisecond
        clear(); // for simplicity
        horizon = newHorizon;
        delta = horizon / precision; // may become negative or zero
    }
}