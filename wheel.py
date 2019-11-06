import pygame
import sys
import math

white = (255,255,255)
black = (0,0,0)
salmon = (250,128,114)
(width, height) = (650, 150)

radius = 35
pt_sz = 4
h_ground = int(0.8*height)
x_center = 0
ang_vel = 0.0003
angle = 0.0
x_pt = 0
y_pt = 0
points = []

N = 200
dt = 1e-2
t = 0.0
cont = 0

def wheel_boundary(x):
    if x > width - radius:
        x = width - radius

    return(x)

def dot_boundary(angle):
    while angle > 2.0 * math.pi:
        angle -= 2.0 * math.pi

    return(angle)

# Create screen
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Wheel')
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
    
    for n in range(N):
        screen.fill(white)

        x_center = radius + int(t)
        x_center = wheel_boundary(x_center)

        if x_center < width - radius:
            cont += 1
            angle += ang_vel
            angle = dot_boundary(angle)
            x_pt = x_center + int(radius * math.sin(angle))
            y_pt = h_ground - radius - int(radius * math.cos(angle))
            if cont%310 == 0:
                points.append((x_pt, y_pt))

        pygame.draw.line(screen, black, (0, h_ground), (width, h_ground))
        pygame.draw.circle(screen, black, (x_center, h_ground - radius), radius, 1)
        pygame.draw.circle(screen, salmon, (x_pt, y_pt), pt_sz)
        for p in points:
            pygame.draw.circle(screen, salmon, p, pt_sz)

        t += dt

    pygame.display.flip()