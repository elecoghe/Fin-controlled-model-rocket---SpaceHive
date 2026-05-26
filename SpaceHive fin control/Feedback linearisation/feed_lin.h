//Feedback linearization library
//Authors: Elena Coghe, Claudia Angelo, Micol Favretto, Matilde Rizzo

#ifndef FEED_LIN_H
#define FEED_LIN_H

#include <math.h>

struct RocketParams {
    float Ix;         // Inertia moment [kg·m²]
    float b;          // Aerodynamic friction
    float C_alpha;    // Wind torque
    float K_ail;      // Fin capacitance [N·m/rad]
    float delta_max;  // Maximum deflection [rad]
};

class Feedback_lin {
private:
    RocketParams _p;
    float _g;      //static term in the real equation, pre-computed
    float _f;      //nonlinear function in the real equation, to be updated online
    float _v;      //regulator input   

public:
    Feedback_lin(const RocketParams& p);

    //Every loop is called out with current state
    // e         : pitch - pitch_ref  [rad]
    // pitch_dot : angular velocity [rad/s]
    // alpha_eff : pitch - phi_wind   [rad]
    // v         : regulator input [rad/s²]
    void update(float e, float pitch_dot, float alpha_eff, float v);

    // Expected fin deflection [rad], with proper saturation (in our case, max 15)
    float real_u() const;

    float get_f() const { return _f; }
    float get_g() const { return _g; }
    float get_v() const { return _v; }
};

#endif // FEED_LIN_H
