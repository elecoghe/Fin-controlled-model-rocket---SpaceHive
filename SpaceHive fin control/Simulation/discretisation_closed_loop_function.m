s = tf('s');
G = 1/s^2;

G_disc = c2d(G, 20e-3, 'tustin');
L = G_disc/(1+G_disc);

step(L);

