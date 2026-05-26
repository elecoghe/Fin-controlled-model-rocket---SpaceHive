s = tf('s');
G = 1/s^2;

G_disc = c2d(G, 20e-3, 'tustin'); %%Tustin discretisation approach, sampling time 20 ms (due to DC brushless dynamics)
L = G_disc/(1+G_disc);

step(L);

