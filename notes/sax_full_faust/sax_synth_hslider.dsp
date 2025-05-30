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


gain = hslider("gain", 0, 0, 1, 0.01);
harmonics_Cs3 = harmonicBank(138.59, 0.555, 0.819, 0.410, 0.910, 1.000, 0.404, 0.137, 0.042, 0.130, 0.174);
harmonics_D3 = harmonicBank(146.83, 0.412, 0.662, 0.454, 0.635, 1.000, 0.425, 0.220, 0.065, 0.037, 0.115);
harmonics_Ds3 = harmonicBank(155.56, 0.639, 1.000, 0.813, 0.633, 0.923, 0.179, 0.084, 0.223, 0.182, 0.150);
harmonics_E3 = harmonicBank(164.81, 0.599, 1.000, 0.806, 0.677, 0.474, 0.164, 0.192, 0.198, 0.172, 0.091);
harmonics_F3 = harmonicBank(174.61, 0.860, 0.987, 1.000, 0.617, 0.076, 0.498, 0.396, 0.210, 0.090, 0.091);
harmonics_Fs3 = harmonicBank(185.00, 0.727, 0.936, 1.000, 0.297, 0.125, 0.236, 0.087, 0.075, 0.109, 0.080);
harmonics_G3 = harmonicBank(196.00, 0.738, 1.000, 0.591, 0.159, 0.165, 0.080, 0.082, 0.086, 0.083, 0.086);
harmonics_Gs3 = harmonicBank(207.65, 0.652, 1.000, 0.331, 0.079, 0.160, 0.110, 0.083, 0.083, 0.054, 0.046);
harmonics_A3 = harmonicBank(220.00, 0.842, 1.000, 0.106, 0.222, 0.319, 0.083, 0.079, 0.139, 0.064, 0.092);
harmonics_As3 = harmonicBank(233.08, 0.667, 1.000, 0.096, 0.123, 0.178, 0.154, 0.092, 0.043, 0.066, 0.066);
harmonics_B3 = harmonicBank(246.94, 0.995, 1.000, 0.105, 0.294, 0.104, 0.195, 0.100, 0.081, 0.092, 0.071);
harmonics_C4 = harmonicBank(261.63, 1.000, 0.513, 0.063, 0.415, 0.056, 0.134, 0.075, 0.096, 0.079, 0.066);
harmonics_Cs4 = harmonicBank(277.18, 1.000, 0.129, 0.049, 0.221, 0.056, 0.099, 0.084, 0.080, 0.089, 0.084);
harmonics_D4 = harmonicBank(293.66, 1.000, 0.246, 0.059, 0.088, 0.106, 0.068, 0.059, 0.048, 0.015, 0.032);
harmonics_Ds4 = harmonicBank(311.13, 1.000, 0.462, 0.412, 0.225, 0.234, 0.024, 0.171, 0.145, 0.162, 0.073);
harmonics_E4 = harmonicBank(329.63, 1.000, 0.382, 0.140, 0.217, 0.288, 0.099, 0.067, 0.129, 0.115, 0.069);
harmonics_F4 = harmonicBank(349.23, 1.000, 0.422, 0.719, 0.096, 0.162, 0.072, 0.083, 0.072, 0.046, 0.040);
harmonics_Fs4 = harmonicBank(369.99, 1.000, 0.396, 0.279, 0.372, 0.117, 0.101, 0.070, 0.000, 0.000, 0.000);
harmonics_G4 = harmonicBank(392.00, 1.000, 0.166, 0.108, 0.166, 0.098, 0.000, 0.135, 0.000, 0.000, 0.000);
harmonics_Gs4 = harmonicBank(415.30, 1.000, 0.115, 0.184, 0.075, 0.063, 0.094, 0.117, 0.042, 0.028, 0.005);
harmonics_A4 = harmonicBank(440.00, 1.000, 0.180, 0.196, 0.094, 0.083, 0.050, 0.040, 0.017, 0.000, 0.000);
harmonics_As4 = harmonicBank(466.16, 1.000, 0.167, 0.297, 0.030, 0.071, 0.062, 0.029, 0.000, 0.000, 0.000);
harmonics_B4 = harmonicBank(493.88, 1.000, 0.174, 0.357, 0.012, 0.001, 0.074, 0.000, 0.000, 0.000, 0.000);
harmonics_C5 = harmonicBank(523.25, 0.920, 0.270, 1.000, 0.001, 0.001, 0.001, 0.000, 0.000, 0.001, 0.000);
harmonics_Cs5 = harmonicBank(554.37, 0.530, 0.121, 1.000, 0.465, 0.519, 0.239, 0.078, 0.109, 0.004, 0.001);
harmonics_D5 = harmonicBank(587.33, 1.000, 0.371, 0.925, 0.561, 0.325, 0.128, 0.048, 0.034, 0.017, 0.038);
harmonics_Ds5 = harmonicBank(622.25, 1.000, 0.182, 0.191, 0.586, 0.201, 0.078, 0.002, 0.001, 0.001, 0.002);
harmonics_E5 = harmonicBank(659.26, 1.000, 0.217, 0.350, 0.001, 0.001, 0.000, 0.001, 0.000, 0.001, 0.000);
harmonics_F5 = harmonicBank(698.46, 1.000, 0.818, 0.950, 0.097, 0.307, 0.001, 0.000, 0.000, 0.000, 0.001);
harmonics_Fs5 = harmonicBank(739.99, 1.000, 0.417, 0.184, 0.157, 0.021, 0.023, 0.007, 0.018, 0.020, 0.032);
harmonics_G5 = harmonicBank(783.99, 1.000, 0.174, 0.134, 0.138, 0.037, 0.000, 0.018, 0.001, 0.000, 0.000);
harmonics_Gs5 = harmonicBank(830.61, 1.000, 0.161, 0.207, 0.141, 0.032, 0.016, 0.006, 0.015, 0.016, 0.005);

selector = hslider("note", 0, 0, 31, 1);

process = ba.selectn(32, selector, harmonics_Cs3, harmonics_D3, harmonics_Ds3, harmonics_E3, harmonics_F3, harmonics_Fs3, harmonics_G3, harmonics_Gs3, harmonics_A3, harmonics_As3, harmonics_B3, harmonics_C4, harmonics_Cs4, harmonics_D4, harmonics_Ds4, harmonics_E4, harmonics_F4, harmonics_Fs4, harmonics_G4, harmonics_Gs4, harmonics_A4, harmonics_As4, harmonics_B4, harmonics_C5, harmonics_Cs5, harmonics_D5, harmonics_Ds5, harmonics_E5, harmonics_F5, harmonics_Fs5, harmonics_G5, harmonics_Gs5) * gain;