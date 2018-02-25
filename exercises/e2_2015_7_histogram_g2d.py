#!/usr/bin/env python3
'''
@author  Michele Tomaiuolo - http://www.ce.unipr.it/people/tomamic
@license This software is free - http://www.gnu.org/licenses/gpl.html
'''

import game2d as g2d

values = []

max_val = 0
val = float(input('Val? '))
while val > 0:
    gray = float(input('Gray? '))
    values.append((val, gray))
    if val > max_val:
        max_val = val
    val = float(input('Val? '))

WIDTH, HEIGHT = 600, 400
g2d.init_canvas((WIDTH, HEIGHT))

if len(values) > 0:
    w = WIDTH / len(values)
    h = HEIGHT / max_val

    for i in range(len(values)):
        val, gray = values[i]
        rect = int(w * i), int(HEIGHT - h * val), int(w - 1), int(h * val)
        g2d.draw_rect((gray, gray, gray), rect)
