set terminal png medium size 640,640 background '#FFFFFF'
set key off
set output 'tmp.png'

set style line 1 linetype rgb 'red' 
plot 'test.dat' with lines linestyle 1