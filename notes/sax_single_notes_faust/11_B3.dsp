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

harmonics_B3 = harmonicBank(246.94, 0.995, 1.000, 0.105, 0.294, 0.104, 0.195, 0.100, 0.081, 0.092, 0.071);

process = harmonics_B3;