import pygame
import sys
import random
import math

# Constants
white = (255,255,255)
black = (0,0,0)
blue = (0,0,255)
(width, height) = (600, 600)
std_size = 5
GRAVITY = 9.8
LENGHT = 0.3
M_TO_PIXEL = 400.0
X_ORIGIN = 0.5
Y_ORIGIN = 0.5
X0 = int(width*X_ORIGIN)
Y0 = int(height*Y_ORIGIN)

# First angle
theta = math.pi * random.random()
thetadot = 0.0
thetadotdot = 0.0

# Second angle
phi = math.pi * random.random()
phidot = 0.0
phidotdot = 0.0

# Variables for time intervals
N = 550
dt = 7e-5
t = 0.0

def boundary_conditions(angle):
    # Both angles can vary from zero to 2 * PI radians.
    while angle > 2.0 * math.pi:
        angle -= 2.0 * math.pi
        
    while angle < 0.0:
        angle += 2.0 * math.pi

    return(angle)

def draw_double_pendulum(screen, theta, phi):    
    x1 = X0 + int(LENGHT * M_TO_PIXEL * math.sin(theta))
    y1 = Y0 + int(LENGHT * M_TO_PIXEL * math.cos(theta))
    x2 = x1 + int(LENGHT * M_TO_PIXEL * math.sin(phi))
    y2 = y1 + int(LENGHT * M_TO_PIXEL * math.cos(phi))

    pygame.draw.circle(screen, blue, (X0, Y0), std_size)
    pygame.draw.line(screen, black, (X0, Y0), (x1, y1))
    pygame.draw.circle(screen, blue, (x1, y1), std_size)
    pygame.draw.line(screen, black, (x1, y1), (x2, y2))
    pygame.draw.circle(screen, blue, (x2, y2), std_size)

# Create screen
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Double pendulum')
screen.fill(white)

print("Initial angles: theta = " + str(theta) + "   phi = " + str(phi))

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
        # Equation of motion for theta
        thetadotdot = (GRAVITY * (0.5 * math.sin(phi) * math.cos(theta - phi) -\
            math.sin(theta)) / LENGHT - 0.5 * math.sin(theta - phi) * (pow(phidot, 2) +\
            pow(thetadot, 2) * math.cos(theta - phi))) / (1.0 - 0.5 * pow(math.cos(theta - phi), 2))

        # Equation of motion for phi
        phidotdot = ((pow(thetadot, 2) + 0.5 * pow(phidot, 2) *\
            math.cos(theta - phi)) * math.sin(theta - phi) + GRAVITY * (math.sin(theta) *\
            math.cos(theta - phi) - math.sin(phi)) / LENGHT) / (1.0 - 0.5 *\
            pow(math.cos(theta - phi), 2))

        thetadot += dt * thetadotdot
        phidot   += dt * phidotdot

        theta += dt * thetadot
        theta = boundary_conditions(theta)
        phi += dt * phidot
        phi = boundary_conditions(phi)
        t += dt
    
        draw_double_pendulum(screen, theta, phi)

    pygame.display.flip()