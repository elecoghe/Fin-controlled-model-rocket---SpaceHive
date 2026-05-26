#include "feed_lin.h"

Feedback_lin::Feedback_lin(const RocketParams& p)
    : _p(p),
      _g(p.K_ail / p.Ix),
      _f(0.0f),
      _v(0.0f)
{}

void Feedback_lin::update(float e, float pitch_dot, float alpha_eff, float v)
{
    (void)e; // feed-forward term for future extensions

    // Nonlinear equation
    float damp = -(_p.b       / _p.Ix) * pitch_dot  * fabsf(pitch_dot);
    float wind = -(_p.C_alpha / _p.Ix) * alpha_eff  * fabsf(alpha_eff);
    _f = damp + wind;

    //Regulator input
    _v = v;
}

float Feedback_lin::real_u() const
{
    float delta_a = (_v - _f) / _g;

    if (delta_a >  _p.delta_max) return  _p.delta_max;
    if (delta_a < -_p.delta_max) return -_p.delta_max;
    return delta_a;
}
