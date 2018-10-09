# Stopwatch Segment Display
Arduino powered stopwatch. Displays the current time with decimals to seven-segment displays.

Real time stop watch displaying to 4 7-segment displays. Uses two shift registers. One controls the 8 bits of the segments, and the second controls which segment is being displayed. The loop displays one digit at a time to each display. When the time interval has been reached, the timer count increases.

On the first shift register, the 8 bits of data are wired to all displays. The second shift register then controls which display should be displayed with that number by enabling it's transistor to ground the display and complete the circuit.

### Circuit
![circuit](https://raw.githubusercontent.com/electro2560/stopwatch-segment-display/branch/master/stopwatch circuit_bb.png)
