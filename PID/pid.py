import matplotlib.pyplot as plt

class Man:
    def __init__(self, goal):
        self.goal = goal


def PID(Kp, plant, iteration):
    global e, speed, errors
    e = plant.goal
    errors = []

    for i in range(iteration):
        speed = Kp * e
        errors.append(e)
        e = e - speed

    return errors


man = Man(50)

errors = PID(0.12, man, 40)
print(errors)

plt.plot(errors)
plt.gca().invert_yaxis()
plt.show()