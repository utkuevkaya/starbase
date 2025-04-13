import matplotlib.pyplot as plt

class Drone:
    def __init__(self, goal, weight):
        self.rpm = 0 
        self.error = goal
        self.weight = weight
        self.errors = []

    def move(self):
        lift_force = self.rpm/4                # Made up by me
        movement = lift_force - self.weight
        return movement 

    def PID(self, Kp, Ki, Kd, iteration):
        prev_error = 0

        for i in range(iteration):
            self.errors.append(self.error)
            prev_error = prev_error + self.error * Ki

            p = Kp * self.error
            i = prev_error + self.error * Ki
            if len(self.errors) > 1:
                d = self.errors[-1] - self.errors[-2]
                d *= Kd
            else: 
                d = 0

            self.rpm = p + i + d
        
            movement = self.move()
            new_error = self.error - movement

            if new_error > self.errors[0]:
                self.error = self.errors[0]
            else: 
                self.error = new_error

    def plot(self):
        plt.plot(self.errors)
        plt.gca().invert_yaxis()
        plt.xlabel("Iteration")
        plt.ylabel("Error")
        plt.title("Error Over Time")
        plt.show()


# drone = Drone(5000, 200)
# drone.PID(0.1, 0.0015, 2, 2000)
# drone.plot()

drone = Drone(10000, 250)
drone.PID(0.1, 0.00045, 2.5, 2000)
drone.plot()