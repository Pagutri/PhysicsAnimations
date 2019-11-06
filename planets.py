import pygame
import sys
import math

# Constants
white = (255,255,255)
blue = (0,0,255)
yellow = (255,215,0)
(width, height) = (1000, 600)
p1_size = 10
p2_size = 10
G = 6.673
m1 = 1.989
m2 = m1
d0 = 59.6
#M_TO_PIXEL = 2.0e-9

# Coordinates
x1 = width/4.0
x1dot = 0.0
x1dotdot = 0.0

y1 = height/2.0
y1dot = 0.0
y1dotdot = 0.0

x2 = x1 + d0
x2dot = 0.0
x2dotdot = 0.0

y2 = y1
y2dot = 0.0
y2dotdot = 0.0

# Variables for time intervals
N = 550
dt = 7e-5
t = 0.0
"""
def boundary_conditions(angle):
    # The angle can vary from zero to 2 * PI radians.
    while angle > 2.0 * math.pi:
        angle -= 2.0 * math.pi
        
    while angle < 0.0:
        angle += 2.0 * math.pi

    return(angle)

def draw_planet1(screen, theta, r):    
    M = m2 / (m1 + m2)
    x1 = x_cm + int(r * M_TO_PIXEL * M * math.cos(theta))
    y1 = y_cm - int(r * M_TO_PIXEL * M * math.sin(theta))

    pygame.draw.circle(screen, yellow, (x1, y1), p1_size)

def draw_planet2(screen, theta, r):    
    M = m1 / (m1 + m2)
    x2 = x_cm - int(r * M_TO_PIXEL * M * math.cos(theta))
    y2 = y_cm + int(r * M_TO_PIXEL * M * math.sin(theta))

    pygame.draw.circle(screen, blue, (x2, y2), p2_size)
"""
# Create screen
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Planets')
screen.fill(white)

# Close screen
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            pygame.display.quit()
            pygame.quit()
            sys.exit()
            
    screen.fill(white)
    
    for n in range(N):
        screen.fill(white)
        var = (x2 - x1)**2 + (y2 - y1)**2
        var = G*pow(var,-1.5)

        # Equations of motion
        x1dotdot = var*m2*(x2 - x1)
        y1dotdot = var*m2*(y2 - y1)
        x2dotdot = -var*m1*(x2 - x1)
        y2dotdot = -var*m1*(y2 - y1)

        x1dot += dt * x1dotdot
        y1dot += dt * y1dotdot
        x2dot += dt * x2dotdot
        y2dot += dt * y2dotdot

        x1 += dt * x1dot
        y1 += dt * y1dot
        x2 += dt * x2dot
        y2 += dt * y2dot

        t += dt
    
        pygame.draw.circle(screen, yellow, (int(x1), int(y1)), p1_size)
        pygame.draw.circle(screen, blue, (int(x2), int(y2)), p2_size)

    pygame.display.flip()