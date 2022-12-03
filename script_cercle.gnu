set size square

#unset key

plot "cercle.dat" index 0 title "Triangle" lc rgb "black" w l, "cercle.dat" index 1 title "Centre" lc rgb "red", "cercle.dat" index 2 title "Cercle" lc rgb "red" w l, "cercle.dat" index 3 title "Point" lc rgb "blue" pointtype 2 pointsize 0.8
