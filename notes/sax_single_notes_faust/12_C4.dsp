import("stdfaust.lib");

harmonicBank(f, g1, g2, g3, g4, g5, g6, g7, g8, g9, g10) = 
    os.osc(1*f) * g1 + 
    os.osc(2*f) * g2 + 
    os.osc(3*f) * g3 + 
    os.osc(4*f) * g4 + 
    os.osc(5*f) * g5 + 
    os.osc(6*f) * g6 + 
    os.osc(7*f) * g7 + 
    os.osc(8*f) * g8 + 
    os.osc(9*f) * g9 + 
    os.osc(10*f) * g10;

harmonics_C4 = harmonicBank(261.63, 1.000, 0.513, 0.063, 0.415, 0.056, 0.134, 0.075, 0.096, 0.079, 0.066);

process = harmonics_C4;